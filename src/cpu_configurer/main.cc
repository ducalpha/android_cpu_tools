// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)


#include <cstdlib>
#include <string>

#include "cpu_configurer/cpu_configurer.h"

#include "base/command_line.h"
#include "base/logging.h"


namespace switches {
  // Set auto hotplug if the user knows, if not need to auto detect
  const char kAutoHotplug[] = "auto-hotplug";

  // Turn on or off the auto hotplug mechanism ("on" or "off")
  const char kSetAutoHotplug[] = "set-auto-hotplug";

  // Set number of online cores
  // Cores [0..num-cores-enabled - 1] will be set online
  const char kNumOnlineCores[] = "num-online-cores";

  // Set frequency governor
  const char kGovernor[] = "governor";

  // Set maximum frequency (in KHz) for the online cores
  const char kMaxFreq[] = "max-freq";

  // Set maximum frequency (in KHz) for the online cores
  const char kMinFreq[] = "min-freq";

  // Max core id = num cores - 1 - min_core_id
  // Assume min_core_id = 0
  const char kMaxCoreId[] = "max-core-id";

  namespace values {
    // Turn on/off values
    const char kOn[] = "on";
    const char kOff[] = "off";
  }
}

// Maximum number of cores on CPUs
const int kMaxNumCores = 8;

// This class provides a convenient way to set CPU's frequencies and number of on cores
// It does not have any assumption about the underlying system
// It's the responsibility of the caller to use this program depending on the system
// mpdecision and dm-hotplug options are mutual exclusive but one of them must present
// TODO: auto detect mpdecision or dm-hotplug should be turned off on underlying system
// Procedure:
//    Disable auto-hotplug
//    Enable n cores (and disable remaining cores)
//    Set frequency governor
//    Set max frequency for each core
//    Set min frequency for each core
//    Enable auto-hotplug if needed
int main(int argc, char **argv) {
  base::CommandLine cmdline(argc, argv);
  android_tools::CpuConfigurer cpu_configurer;

  if (cmdline.HasSwitch(switches::kMaxCoreId)) {
    size_t max_core_id = std::atoi(cmdline.GetSwitchValue(switches::kMaxCoreId));
    cpu_configurer.SetMaxCoreId(max_core_id);
  }

  // Disable hotplug daemon/mechanism
  // TODO: auto detect cpu management daemon and auto hotplug mechanism
  std::string auto_hotplug_option = cmdline.GetSwitchValue(switches::kAutoHotplug);

  cpu_configurer.SetAutoHotplug(auto_hotplug_option);

  std::string set_auto_hotplug_option = cmdline.GetSwitchValue(switches::kSetAutoHotplug);
  // Always disable auto hotplug first
  // TODO: unify mpdecision and dm-hotplug size_to auto-hotplug
  if (set_auto_hotplug_option == switches::values::kOn || 
      set_auto_hotplug_option == switches::values::kOff) {
    cpu_configurer.SetAutoHotplugMechanism(false);
  } else {
    LOG(ERROR) << "Invalid values for set auto hotplug option: " << set_auto_hotplug_option;
  }

  if (cmdline.HasSwitch(switches::kNumOnlineCores)) {
    size_t num_online_cores = std::stoul(cmdline.HasSwitch(switches::kNumOnlineCores));
    cpu_configurer.SetNumOnlineCores(num_online_cores);
  }

  if (cmdline.HasSwitch(switches::kGovernor)) {
    cpu_configurer.SetGovernorForOnlineCores(cmdline.GetSwitchValue(switches::kGovernor));
  }

  ;
  if (cmdline.HasSwitch(switches::kMaxFreq)) {
    cpu_configurer.SetMaxFreqForOnlineCores(cmdline.GetSwitchValue(switches::kMaxFreq),
                                            num_online_cores);
  }

  if (cmdline.HasSwitch(switches::kMinFreq)) {
    cpu_configurer.SetMinFreqForOnlineCores(cmdline.GetSwitchValue(switches::kMinFreq),
                                            num_online_cores);
  }

  // Enabled auto-hotplug if needed
  if (set_auto_hotplug_option == switches::values::kOn) {
    cpu_configurer.SetAutoHotplug(true);
  }

  return 0;
}
