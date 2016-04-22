// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($LICENSE_URL)

#ifndef BASE_THREADING_PLATFORM_THREAD_H_
#define BASE_THREADING_PLATFORM_THREAD_H_

#include <sys/types.h> // for pid_t
#include <vector>

// This file emulates the base/threading/platform_thread in Chromium project
// Provides functions to set thread's affinity

namespace base {

typedef pid_t PlatformThreadId;

class PlatformThread {
 public:
  // Set the current thread to run on certain cpu cores
  static void SetCurrentThreadAffinity(const std::vector<int>& eligible_core_ids);

  // Set a thread to run on certain cpus
  // Return false in case of failure (e.g., the caller does not have permission)
  static void SetThreadAffinity(PlatformThreadId tid, const std::vector<int>& eligible_core_ids);
};
}  // namespace base

#endif  // BASE_THREADING_PLATFORM_THREAD_H_
