// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_TOOLS_CPU_INFO_CPU_INFO_H_
#define ANDROID_TOOLS_CPU_INFO_CPU_INFO_H_

#include "base/command_line.h"

#include <string>
#include <vector>

namespace android_cpu_tools {

struct CpuClusterInfo {
  size_t min_core_id, max_core_id, min_freq, max_freq;
  std::string freq_governor;
};

class CpuInfo {
 public:
  CpuInfo();

  // Initialize cpu info by reading information from /sys
  void PopulateClusterInfo();

  // Initialize cpu info provided a command line instance
  bool InitializeFromCommandLine(const base::CommandLine& command_line);

  size_t MaxCoreId() const { return max_core_id_; }

  size_t MinCoreId() const { return min_core_id_; }

  std::string AutoHotplug() const { return auto_hotplug_; }

  // Return cpu info in form of Chrome command line
  std::string ToChromeCommandLine() const;

  const std::vector<CpuClusterInfo>& CpuClusterInfos() const {
    return cpu_cluster_infos_;
  }

 private:

  enum class FreqType : int {
    MIN,
    CURRENT,
    MAX
  };

  bool ReadMinMaxCoreIds();

  // Return min/cur/max freq
  // Return 0 in case of failure
  size_t ReadFreqOfCore(FreqType freq_type, size_t core_id);

  CpuClusterInfo ReadClusterInfoOfCore(size_t core_id);
  std::string ReadFreqGovernorOfCore(size_t core_id);

  size_t min_core_id_, max_core_id_;

  std::string auto_hotplug_;

  // This is sorted by max freq
  std::vector<CpuClusterInfo> cpu_cluster_infos_;
};

}  // namespace android_cpu_tools

#endif  // ANDROID_TOOLS_CPU_INFO_CPU_INFO_H_
