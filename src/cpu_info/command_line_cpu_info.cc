// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

#include "cpu_info/cpu_info.h"

#include "base/command_line.h"
#include "base/logging.h"
#include "base/strings/string_split.h"
#include "cpu_info/cpu_info.h"
#include "cpu_info/cpu_info_switches.h"

#include <cstdio>

// Only Chromium supports LazyInstance
#if defined(CHROMIUM_BUILD)
#include "base/lazy_instance.h"
#endif

namespace {

class LazyCpuInfo {
 public:
  LazyCpuInfo();

  // Initialize cpu info provided a command line instance
  bool InitializeFromCommandLine();

  size_t min_core_id, max_core_id;

  std::string auto_hotplug;

  // This is sorted by max freq
  std::vector<android_cpu_tools::CpuClusterInfo> cpu_cluster_infos;
};

LazyCpuInfo::LazyCpuInfo()
  : min_core_id(0),
    max_core_id(7),
    auto_hotplug("dm-hotplug") {
  if (!InitializeFromCommandLine()) {
      LOG(ERROR) << "Error initializing cpu_info from command line";
  }
}

bool LazyCpuInfo::InitializeFromCommandLine() {
  const base::CommandLine& command_line = *base::CommandLine::ForCurrentProcess();

  std::string cpu_core_ids_str =
      command_line.GetSwitchValueASCII(switches::kCpuCoreIds);

  if (cpu_core_ids_str.empty()) {
    LOG(ERROR) << switches::kCpuCoreIds << " is not available";
    return false;
  }

  if (sscanf(cpu_core_ids_str.c_str(), "%zu-%zu", &min_core_id, &max_core_id) != 2) {
    LOG(ERROR) << "Error parsing core ids : " << cpu_core_ids_str;
    return false;
  }

  std::string cluster_core_ids_str =
      command_line.GetSwitchValueASCII(switches::kClusterCoreIds);
  std::string cluster_freqs_str =
      command_line.GetSwitchValueASCII(switches::kClusterFreqs);
  std::string cluster_freq_governors_str =
      command_line.GetSwitchValueASCII(switches::kClusterFreqGovernors);

  if (cluster_core_ids_str.empty() || cluster_freqs_str.empty() ||
      cluster_freq_governors_str.empty()) {
    LOG(ERROR) << "Some cluster information is not available";
    return false;
  }

  std::vector<std::string> cluster_core_ids;
  std::vector<std::string> cluster_freqs;
  std::vector<std::string> cluster_freq_governors;

  cluster_core_ids = base::SplitString(cluster_core_ids_str, ",", base::WhitespaceHandling::TRIM_WHITESPACE,
      base::SplitResult::SPLIT_WANT_NONEMPTY);
  cluster_freqs = base::SplitString(cluster_freqs_str, ",", base::WhitespaceHandling::TRIM_WHITESPACE,
      base::SplitResult::SPLIT_WANT_NONEMPTY);
  cluster_freq_governors = base::SplitString(cluster_freq_governors_str, ",", base::WhitespaceHandling::TRIM_WHITESPACE,
      base::SplitResult::SPLIT_WANT_NONEMPTY);

  if (!(cluster_core_ids.size() == cluster_freqs.size() && 
        cluster_freq_governors.size() == cluster_core_ids.size() &&
        !cluster_core_ids.empty())) {
    LOG(INFO) << cluster_core_ids.size();
    LOG(INFO) << cluster_freqs.size();
    LOG(INFO) << cluster_freq_governors.size();
    LOG(ERROR) << "Cluster information mismatches";
    return false;
  }

  cpu_cluster_infos.resize(cluster_core_ids.size());

  for (size_t i = 0; i < cluster_core_ids.size(); ++i) {
    if (sscanf(cluster_core_ids[i].c_str(), "%zu-%zu",
          &cpu_cluster_infos[i].min_core_id,
          &cpu_cluster_infos[i].max_core_id) != 2) {
      LOG(ERROR) << "Error parsing cluster core id : " << cluster_core_ids[i];
      return false;
    }
    
    if (sscanf(cluster_freqs[i].c_str(), "%zu-%zu",
          &cpu_cluster_infos[i].min_freq,
          &cpu_cluster_infos[i].max_freq) != 2) {
      LOG(ERROR) << "Error parsing cluster freqs : " << cluster_freqs[i];
      return false;
    }

    cpu_cluster_infos[i].freq_governor = cluster_freq_governors[i];
  }
  

  auto_hotplug = command_line.GetSwitchValueASCII(switches::kAutoHotplug);
  if (auto_hotplug.empty()) {
    LOG(ERROR) << "Auto hotplug information is unavailable";
    return false;
  }

  return true;
}


#if defined(CHROMIUM_BUILD)
base::LazyInstance<LazyCpuInfo> g_lazy_cpu_info = LAZY_INSTANCE_INITIALIZER;
#else
LazyCpuInfo *g_lazy_cpu_info;
#endif

LazyCpuInfo& GlobalCpuInfo() {
#if defined(CHROMIUM_BUILD)
  return g_lazy_cpu_info.Get();
#else
  if (!g_lazy_cpu_info) {
    g_lazy_cpu_info = new LazyCpuInfo();
    if (!g_lazy_cpu_info) {
      LOG(FATAL) << "Cannot allocat cpu info";
    }
  }
  return *g_lazy_cpu_info;
#endif
}

}  // namespace

namespace android_cpu_tools {

// static
size_t CommandLineCpuInfo::MinCoreId() {
  return GlobalCpuInfo().min_core_id;
}

// static
size_t CommandLineCpuInfo::MaxCoreId() {
  return GlobalCpuInfo().max_core_id;
}

// static
size_t CommandLineCpuInfo::MinFreq() {
  static size_t min_freq = 0;
  if (min_freq > 0)
    return min_freq;

  const std::vector<android_cpu_tools::CpuClusterInfo>& cpu_cluster_infos =
      CpuClusterInfos();
  for (size_t i = 0; i < cpu_cluster_infos.size(); ++i) {
    if (min_freq == 0 || min_freq > cpu_cluster_infos[i].min_freq) {
      min_freq = cpu_cluster_infos[i].min_freq;
    }
  }

  return min_freq;
}

// static
size_t CommandLineCpuInfo::MaxFreq() {
  static size_t max_freq = 0;
  if (max_freq > 0)
    return max_freq;

  const std::vector<android_cpu_tools::CpuClusterInfo>& cpu_cluster_infos =
     CpuClusterInfos();
  for (size_t i = 0; i < cpu_cluster_infos.size(); ++i) {
    if (max_freq < cpu_cluster_infos[i].max_freq) {
      max_freq = cpu_cluster_infos[i].max_freq;
    }
  }

  return max_freq;
}

// static
std::string CommandLineCpuInfo::FirstFreqGovernor() {
  const std::vector<android_cpu_tools::CpuClusterInfo>& cpu_cluster_infos =
    CpuClusterInfos();
  if (cpu_cluster_infos.empty()) {
    LOG(ERROR) << "Cpu cluster info is empty";
    return "";
  }

  return cpu_cluster_infos.front().freq_governor;
}

// static
std::string CommandLineCpuInfo::AutoHotplug() {
  return GlobalCpuInfo().auto_hotplug;
}

// static
const std::vector<android_cpu_tools::CpuClusterInfo>& CommandLineCpuInfo::CpuClusterInfos() {
  return GlobalCpuInfo().cpu_cluster_infos;
}

}  // namespace android_cpu_tools
