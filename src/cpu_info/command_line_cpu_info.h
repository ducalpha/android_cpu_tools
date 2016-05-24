// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_CPU_TOOLS_CPU_INFO_COMMAND_LINE_CPU_INFO_H_
#define ANDROID_CPU_TOOLS_CPU_INFO_COMMAND_LINE_CPU_INFO_H_

#include "base/third_party/android_cpu_tools/src/cpu_info/cpu_info.h"

#include <string>
#include <vector>

// TODO: merge this class to android_cpu_tools::CpuInfo
// This class is temporarily for supporting compilation without C++11 (e.g., Chromium v38)
// Will merge to CpuInfo class when moving newer version of Chromium
namespace android_cpu_tools {

class CommandLineCpuInfo {
 public:
  CpuInfo();

  static size_t MinCoreId();
  static size_t MaxCoreId();

  static size_t MinFreq();
  static size_t MaxFreq();

  static std::string AutoHotplug();
  static const std::vector<android_cpu_tools::CpuClusterInfo>& CpuClusterInfos();

  // Frequency governor of the first cpu
  // Typically, governors of all cores are the same
  static std::string FirstFreqGovernor();
};

}  // namespace base

#endif  // ANDROID_CPU_TOOLS_CPU_INFO_COMMAND_LINE_CPU_INFO_H_
