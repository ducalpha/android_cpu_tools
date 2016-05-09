// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_TOOLS_CPU_CONFIGURER_CPU_CONFIGURER_H_
#define ANDROID_TOOLS_CPU_CONFIGURER_CPU_CONFIGURER_H_

#include <memory>
#include <string>

#include "cpu_configurer/auto_hotplug.h"

namespace android_cpu_tools {

// Configure settings for cpus: frequencies, governor, auto hotplug
class CpuConfigurer {
 public:
  CpuConfigurer(size_t max_core_id);

  void SetAutoHotplugType(const std::string& type);
  void SetAutoHotplugEnabled(bool enabled);

  // Enable num_cores, disable the remaining
  void SetNumOnlineCores(size_t num_cores);

  void SetGovernorForOnlineCores(const std::string& governor);

  /* if we know num online core, we can avoid opening offline core's sysfs file */
  void SetMaxFreqForOnlineCores(const std::string& freq_khz);
  void SetMinFreqForOnlineCores(const std::string& freq_khz);

 private:
  void SetCoreEnabled(size_t core_id, bool enabled);

  void SetGovernorForCore(const std::string& governor, size_t core_id);
  void SetMaxFreqForCore(const std::string& freq_khz, size_t core_id);
  void SetMinFreqForCore(const std::string& freq_khz, size_t core_id);

  size_t max_core_id_ = 7; // max num cores in modern SoC is 8
  size_t num_online_cores_ = max_core_id_ + 1;
  // Assume min_core_id = 0

  std::unique_ptr<AutoHotplug> auto_hotplug_;
};

}  // namespace android_cpu_tools

#endif  // ANDROID_TOOLS_CPU_CONFIGURER_CPU_CONFIGURER_H_
