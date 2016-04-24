// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.

#ifndef BROWSER_PROFILER_WORKLOAD_GENERATOR_H_
#define BROWSER_PROFILER_WORKLOAD_GENERATOR_H_

#include "base/logging.h"
#include "base/threading/platform_thread.h"

#include <pthread.h>
#include <pthread.h>
#include <sys/resource.h> // for setpriority()
#include <unistd.h>
#include <vector>

namespace browser_profiler {

namespace {
void SetCurrentThreadMaxPriority() {
#if defined(OS_ANDROID)
  const int kMaxPriority = -20; // max priority on Linux

  if (setpriority(PRIO_PROCESS, 0, kMaxPriority) < 0) {
    PLOG(ERROR) << "setpriority failed";
  }
}
#endif

// Some workload that the compiler cannot optimize away
void RealWorkload(int load_length) {
  // This workload has complexity of O(load_length^2)
  // A big core of Exynos 5422, load_length 10000, runs in 0.9 sec
  int i = 1;
  bool k = false;
  for (int j = 0; j < load_length; ++j) {
    for (i = 1; i < j; ++i) {
      if ((j % i) == 0)
        k = true;
    }
  }

  // This effectively prevents gcc optimization
  printf("%d\n", k);
}

}  // namespace


class WorkloadGenerator {
 public:

  // Perform a single/multi-threaded 100%-utilization workload on the given cpu cores
  // The number of threads == number of given cores (one thread per core)
  // load_length is relative, the bigger the value, the longer the workload
  // TODO: check the number of threads with number of cores
  // NOTE: This function assumes the appropriate cpu cores are on
  // due to cpu cores' hotplugs, this function requires 
  // appropriate cpu setting before running (set frequency + cpu turned on)
  static void RunWorkload(const std::vector<int>& eligible_cores, int load_length) {
    sync(); // sync all files to prevent interence during workload

    // Create workload threads
    std::vector<pthread_t> workload_tids(eligible_cores.size());

    for (size_t i = 0; i < workload_tids.size(); ++i) {
      WorkloadParams *workload_params = new WorkloadParams();
      workload_params->eligible_core = eligible_cores[i];
      workload_params->load_length = load_length;

      if (pthread_create(&workload_tids[i], NULL, Workload, workload_params) < 0) {
        PLOG(ERROR) << "pthread_create failed";
      }
    }

    for (size_t i = 0; i < workload_tids.size(); ++i) {
      if (pthread_join(workload_tids[i], NULL) < 0) {
        PLOG(ERROR) << "pthread_join failed";
      }
    }
  }

 private:

  struct WorkloadParams {
    int eligible_core;
    int load_length;
  };

  static void *Workload(void *arg) {
    const WorkloadParams *workload_params = (const WorkloadParams *) arg;

    base::PlatformThread::SetCurrentThreadAffinity(
                              std::vector<int>(1, workload_params->eligible_core));
    SetCurrentThreadMaxPriority(); 

    VLOG(1) << "Run workload with load_length: " << workload_params->load_length 
              << ", on core " << workload_params->eligible_core;

    RealWorkload(workload_params->load_length);

    delete workload_params;

    return NULL;
  }

};

}  // namespace browser_profiler

#endif // BROWSER_PROFILER_WORKLOAD_GENERATOR_H_
