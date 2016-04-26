// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "cpu_info/cpu_info.h"

#include "base/command_line.h"
#include "base/logging.h"
#include "base/files/file_util.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "cpu_info/cpu_info_switches.h"

// #include <cstdio>

namespace {
const std::string kPossibleCpuPath = "/sys/devices/system/cpu/possible";

std::string TrimTrailingNewLine(std::string input) {
  return base::TrimString(input, "\n", base::TrimPositions::TRIM_TRAILING).as_string();
}
};

namespace android_tools {

// Assume: cpu clusters are sorted increasingly by max frequencies
CpuInfo::CpuInfo() {
  if (!ReadMinMaxCoreIds()) {
    LOG(ERROR) << "Cannot read min and max core ids";
    return;
  }
}

void CpuInfo::PopulateClusterInfo() {
  CpuClusterInfo cur_cluster = ReadClusterInfoOfCore(min_core_id_),
      prev_cluster(cur_cluster);

  size_t prev_cluster_min_core_id = 0;

  for (size_t i = 1; i <= max_core_id_; ++i) {
    cur_cluster = ReadClusterInfoOfCore(i);

    if (cur_cluster.max_freq > prev_cluster.max_freq) {
      cpu_cluster_infos_.emplace_back(CpuClusterInfo{prev_cluster_min_core_id, i - 1, 
          prev_cluster.min_freq, prev_cluster.max_freq, prev_cluster.freq_governor});
      prev_cluster_min_core_id = i;
    }
    prev_cluster = cur_cluster;
  }


  // Always add the last cluster
  cpu_cluster_infos_.emplace_back(CpuClusterInfo{prev_cluster_min_core_id, max_core_id_,
      cur_cluster.min_freq, cur_cluster.max_freq, cur_cluster.freq_governor});
}

CpuClusterInfo CpuInfo::ReadClusterInfoOfCore(size_t core_id) {
  return CpuClusterInfo{core_id, core_id, 
      ReadFreqOfCore(FreqType::MIN, core_id), ReadFreqOfCore(FreqType::MAX, core_id),
      ReadFreqGovernorOfCore(core_id)};
}

size_t CpuInfo::ReadFreqOfCore(FreqType freq_type, size_t core_id) {
  std::string freq_path = "/sys/devices/system/cpu/cpu" + base::UintToString(core_id) + "/cpufreq/cpuinfo_";
  switch (freq_type) {
    case FreqType::MIN:
      freq_path.append("min");
      break;
    case FreqType::CURRENT:
      freq_path.append("cur");
      break;
    case FreqType::MAX:
      freq_path.append("max");
      break;
    default:
      NOTREACHED();
  }
  freq_path.append("_freq");

  std::string freq_str;
  if (!base::ReadFileToString(base::FilePath(freq_path), &freq_str)) {
    LOG(ERROR) << "Failed to read file " << freq_path;
    return 0;
  }

  size_t freq;
  if (!base::StringToUint(TrimTrailingNewLine(freq_str), &freq)) {
    LOG(ERROR) << "Cannot convert max_freq (" << freq_str << ") to number";
    return 0;
  }
  return freq;
}

std::string CpuInfo::ReadFreqGovernorOfCore(size_t core_id) {
  std::string governor_path = "/sys/devices/system/cpu/cpu" + base::UintToString(core_id) + "/cpufreq/scaling_governor";
  std::string governor;
  if (!base::ReadFileToString(base::FilePath(governor_path), &governor)) {
    LOG(ERROR) << "Failed to read file " << governor_path;
    return "";
  }
  return TrimTrailingNewLine(governor);
}

bool CpuInfo::ReadMinMaxCoreIds() {
  std::string min_max_core_ids;
  base::ReadFileToString(base::FilePath(kPossibleCpuPath), &min_max_core_ids);
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

// Assume each cluster has the same min/max freq and freq governor
// --cpu-core-ids=0,3 --cluster-core-ids=0-3,4-7 --cluster-freqs=1000-2000,2000-4000 --cluster-freq-governor=interactive,interactive
std::string CpuInfo::ToChromeCommandLine() const {
  base::CommandLine cmdline(base::CommandLine::NO_PROGRAM);
  std::string cluster_core_ids;
  std::string cluster_freqs;
  std::string cluster_freq_governors;

  for (size_t i = 0; i < cpu_cluster_infos_.size(); ++i) {
    CpuClusterInfo cluster_info = cpu_cluster_infos_[i];
    cluster_core_ids.append(base::UintToString(cluster_info.min_core_id) 
          + "-" + base::UintToString(cluster_info.max_core_id));
    cluster_freqs.append(base::UintToString(cluster_info.min_freq) 
          + "-" + base::UintToString(cluster_info.max_freq));
    cluster_freq_governors.append(cluster_info.freq_governor);

    if (i != cpu_cluster_infos_.size() - 1) {
      cluster_core_ids.append(",");
      cluster_freqs.append(",");
      cluster_freq_governors.append(",");
    }
  }

  cmdline.AppendSwitchASCII(switches::kCpuCoreIds, base::UintToString(min_core_id_) 
        + "-" + base::UintToString(max_core_id_));
  cmdline.AppendSwitchASCII(switches::kClusterCoreIds, cluster_core_ids);
  cmdline.AppendSwitchASCII(switches::kClusterFreqs, cluster_freqs);
  cmdline.AppendSwitchASCII(switches::kClusterFreqGovernors, cluster_freq_governors);

  return cmdline.GetCommandLineString();
}

}  // namespace android_tools
