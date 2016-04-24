// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "workload_generator.h"

#include <cstdio>
#include <vector>

namespace android_tools {
namespace cpu_info {

// Assume: cpu clusters are sorted increasingly by max frequencies
void CpuInfo::CpuInfo() {
  if (!ReadMinMaxCoreIds()) {
    LOG(ERROR) << "Cannot read min and max core ids";
    return;
  }
}

void CpuInfo::PopulateClusterInfo() {
  size_t min_core_id = 0;
  size_t max_max_freq = 0;
  for (size_t i = 0; i <= max_core_id; ++i) {
    size_t cur_max_freq = ReadMaxFreqOfCore(i);
    if (cur_max_freq > max_max_freq) {
      if (i > 0) {
        cluster_info_set.emplace(min_core_id, i - 1, ReadMinFreqOfCore(i - 1), cur_max_freq);
      }
      min_core_id = i; 
      max_max_freq = cur_max_freq;
    }
  }
  cluster_info_set.emplace(min_core_id, max_core_id, ReadMinFreqOfCore(max_core_id), cur_max_freq);
}

size_t CpuInfo::ReadMaxFreqOfCore(size_t core_id) {
  std::string max_freq_path = "/sys/devices/system/cpu/cpu" + std::to_string(core_id) + "/cpufreq/cpuinfo_max_freq";
  std::string max_freq;
  base::ReadFileToString(max_freq_path, max_freq);
  return std::stoul(max_freq);
}

size_t CpuInfo::ReadMinFreqOfCore(size_t core_id) {
  std::string min_freq_path = "/sys/devices/system/cpu/cpu" + std::to_string(core_id) + "/cpufreq/cpuinfo_min_freq";
  std::string min_freq;
  base::ReadFileToString(min_freq_path, min_freq);
  return std::stoul(min_freq);
}

bool CpuInfo::ReadMinMaxCoreIds() {
  std::string min_max_core_ids;
  base::ReadFileToString(kPossibleCpuPath, min_max_core_ids);
  int min_core_id, max_core_id;
  int num_read = sscanf(min_max_core_ids.c_str(), "%d-%d", &min_core_id, &max_core_id);
  if (num_read != 2) {
    LOG(ERROR) << "Cannot parse min and max core ids from string: " << min_max_core_ids;
    return false;
  }
  min_core_id_ = min_core_id;
  max_core_id_ = max_core_id;
  return true;
}

// --cpu-cluster-core-ids=0-3,4-7 --cpu-cluster-freqs=1000-2000,2000-4000 --cpu-core-ids=0,3
std::string CpuInfo::ToChromeCommandLine() {
  CommandLine cmd;
  std::string cluster_core_ids;
  std::string cluster_freqs;
  for (size_t i = 0; i < cpu_cluster_infos_.size(); ++i) {
    CpuClusterInfo cluster_info = cpu_cluster_infos_[i];
    cluster_core_ids.append(cluster_info.min_core_id + "-" + cluster_info.max_core_id);
    cluster_freqs.append(cluster_info.min_freq + "-" + cluster_info.max_freq);
    if (i != cpu_cluster_infos_.size() - 1) {
      cluster_core_ids.append(",");
      cluster_freqs.append(",");
    }
  }
  cmdline.AppendSwitchWithValue(cpu_info::switches::kClusterCoreIds, cluster_core_ids);
  cmdline.AppendSwitchWithValue(cpu_info::switches::kClusterFreqs, cluster_freqs);

  cmdline.AppendSwitchWithValue(cpu_info::switches::kCpuCoreIds, min_core_id_ + "-" + max_core_id_);
  return cmdline.GetCommandLineString();
}

}  // namespace cpu_info 
}  // namespace android_tools
