// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include <cstdlib> // for std::system()

// #include <fcntl.h>

#include "cpu_configurer.h"
#include "base/logging.h"
#include "base/files/file_util.h"
#include "base/strings/string_number_conversions.h"

#include <string>

namespace android_tools {

CpuConfigurer::CpuConfigurer(size_t max_core_id)
: max_core_id_(max_core_id),
  num_online_cores_(max_core_id + 1) {
}

void CpuConfigurer::SetAutoHotplugType(const std::string& type) {
  auto_hotplug_ = AutoHotplug::Create(type);
  if (auto_hotplug_ == nullptr)
    LOG(ERROR) << "Cannot create auto hotplug";
}

void CpuConfigurer::SetAutoHotplugEnabled(bool enabled) {
  if (auto_hotplug_ == nullptr)
    SetAutoHotplugType(""); // auto detect

  if (auto_hotplug_ != nullptr)
    auto_hotplug_->SetEnabled(enabled);
}

// skip first core (core 0) since there must be one always turned on (cannot turn on/off it)
// Enable first num_cores: min_core_id_ -> min_core_id_ + num_cores - 1, disable the others
void CpuConfigurer::SetNumOnlineCores(size_t num_cores) {
  VLOG(1) << "SetNumOnlineCores " << num_cores;
  num_online_cores_ = num_cores;
  for (size_t i = 1; i <= max_core_id_; ++i) {
    if (i <= num_cores - 1) {
      SetCoreEnabled(i, true);
    } else {
      SetCoreEnabled(i, false);
    }
  }
}

void CpuConfigurer::SetCoreEnabled(size_t core_id, bool enabled) {
  std::string setting_path = "/sys/devices/system/cpu/cpu" +
                             base::UintToString(core_id) + "/online";

  VLOG(3) << "SetCoreEnabled " << enabled << " " << setting_path;
  if (!base::WriteFile(base::FilePath(setting_path), enabled ? "1" : "0", 1)) {
    std::string msg = "Cannot ";
    msg.append(enabled ? "enable" : "disable").append(" core ").append(base::UintToString(core_id));
    LOG(ERROR) << msg;
  }
}

void CpuConfigurer::SetGovernorForOnlineCores(const std::string& governor) {
  for (size_t i = 0; i < num_online_cores_; ++i) {
    SetGovernorForCore(governor, i);
  }
}

void CpuConfigurer::SetGovernorForCore(const std::string& governor, size_t core_id) {
  std::string governor_setting_path = "/sys/devices/system/cpu/cpu" + 
                                       base::UintToString(core_id) + "/cpufreq/scaling_governor"; 
  if (!base::WriteFile(base::FilePath(governor_setting_path), governor.c_str(), governor.length())) {
    LOG(ERROR) << "Cannot set governor for core " << core_id;
  }
}

void CpuConfigurer::SetMaxFreqForOnlineCores(const std::string& freq_khz) {
  for (size_t i = 0; i < num_online_cores_; ++i) {
    SetMaxFreqForCore(freq_khz, i);
  }
}

void CpuConfigurer::SetMinFreqForOnlineCores(const std::string& freq_khz) {
  for (size_t i = 0; i < num_online_cores_; ++i) {
    SetMinFreqForCore(freq_khz, i);
  }
}

void CpuConfigurer::SetMaxFreqForCore(const std::string& freq_khz, size_t core_id) {
  std::string coreOnline =
      "/sys/devices/system/cpu/cpu" + base::UintToString(core_id) + "/cpufreq/scaling_max_freq"; 
  if (!base::WriteFile(base::FilePath(coreOnline), freq_khz.c_str(), freq_khz.length())) {
    LOG(ERROR) << "Cannot set max frequency for core " << core_id;
  }
}

void CpuConfigurer::SetMinFreqForCore(const std::string& freq_khz, size_t core_id) {
  std::string coreOnline =
      "/sys/devices/system/cpu/cpu" + base::UintToString(core_id) + "/cpufreq/scaling_min_freq"; 
  if (!base::WriteFile(base::FilePath(coreOnline), freq_khz.c_str(), freq_khz.length())) {
    LOG(ERROR) << "Cannot set min frequency for core " << core_id;
  }
}

}  // namespace android_tools
