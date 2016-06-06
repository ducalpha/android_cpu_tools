// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

#ifndef ANDROID_CPU_TOOLS_WORKLOAD_GENERATOR_WORKLOAD_GENERATOR_H_
#define ANDROID_CPU_TOOLS_WORKLOAD_GENERATOR_WORKLOAD_GENERATOR_H_

#include <pthread.h>
#include <sys/resource.h> // for setpriority()
#include <unistd.h>
#include <vector>

#include "base/logging.h"
#include "base/threading/platform_thread.h"

// Use header-only code to avoid declaring include in the client
namespace android_cpu_tools {

class WorkloadGenerator {

 public:

  // Perform a single/multi-threaded 100%-utilization workload on the given cpu cores
  // The number of threads == number of given cores (one thread per core)
  // load_length is relative, the bigger the value, the longer the workload
  // TODO: check the number of threads with number of cores
  // NOTE: This function assumes the appropriate cpu cores are on
  // due to cpu cores' hotplugs, this function requires 
  // appropriate cpu setting before running (set frequency + cpu turned on)
  // See workload's description to know the appropriate load_length
  static void RunWorkload(const std::vector<size_t>& eligible_cores, int load_length);
};

}  // namespace android_cpu_tools

#endif // ANDROID_CPU_TOOLS_WORKLOAD_GENERATOR_WORKLOAD_GENERATOR_H_
