// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_TOOLS_CPU_CONFIGURER_CPU_CONFIGURER_H_
#define ANDROID_TOOLS_CPU_CONFIGURER_CPU_CONFIGURER_H_

#include <memory>
#include <string>

#include "cpu_configurer/auto_hotplug.h"

namespace android_tools {

// Configure settings for cpus: frequencies, governor, auto hotplug
class CpuConfigurer {
 public:
  void SetMaxCoreId(size_t max_core_id);

  // Auto hotplug setting
  // Let the client convert the string input to AutoHotplug::Type
  // If UNKNOWN is passed, use auto detect
  void SetAutoHotplug(AutoHotplug::Type type);
  void SetAutoHotplugEnabled(bool enabled);
  void SetMpdecisionEnabled(bool enabled);
  void SetDmHotplugEnabled(bool enabled);

  // Enable num_cores, disable the remaining
  void SetNumOnlineCores(size_t num_cores);

  void SetGovernorForOnlineCores(std::string governor);

  /* if we know num online core, we can avoid opening offline core's sysfs file */
  void SetMaxFreqForOnlineCores(std::string freq_khz);
  void SetMinFreqForOnlineCores(std::string freq_khz);

 private:
  void SetCoreEnabled(size_t core_id, bool enabled);
  void SetGovernorForCore(std::string governor, size_t core_id);

  void SetMaxFreqForCore(std::string freq_khz, std::string core_id);
  void SetMinFreqForCore(std::string freq_khz, std::string core_id);
  void SetGovernorForCore(std::string governor, std::string core_id);

  size_t max_core_id_ = 7; // max num cores in modern SoC is 8
  size_t num_online_cores_ = max_core_id_ + 1;
  // Assume min_core_id = 0

  std::unique_ptr<AutoHotplug> auto_hotplug_;
};

}  // namespace android_tools

#endif  // ANDROID_TOOLS_CPU_CONFIGURER_CPU_CONFIGURER_H_
