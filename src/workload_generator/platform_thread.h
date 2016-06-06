// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

#ifndef BROWSER_PROFILER_WORKLOAD_GENERATOR_PLATFORM_THREAD_H_
#define BROWSER_PROFILER_WORKLOAD_GENERATOR_PLATFORM_THREAD_H_

#include <vector>
#include <unistd.h>

namespace android_cpu_tools {

typedef pid_t PlatformThreadId;

// Ported from base/platform_thread with setting affinity
// to make workload_generator portable
// Because workload_generator is the only component which uses setting affinity
// TODO: extract setting affinity to a separate library
class PlatformThread {
 public:
  // ducalpha: the following are used by the Assisted Scheduling
  // Set the current thread to run on certain cpu cores
  static void SetCurrentThreadAffinity(const std::vector<size_t>& eligible_core_ids);

  // Set a thread to run on certain cpus
  // Return false in case of failure (e.g., the caller does not have permission)
  // Use this when you know exact the cores you want to pin the thread to
  static bool SetThreadAffinity(PlatformThreadId tid, const std::vector<size_t>& eligible_core_ids);
};

}  // namespace android_cpu_tools

#endif  // BROWSER_PROFILER_WORKLOAD_GENERATOR_PLATFORM_THREAD_H_
