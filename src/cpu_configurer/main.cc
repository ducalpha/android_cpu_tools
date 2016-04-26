// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)


#include <cstdlib>
#include <string>

#include "cpu_configurer/cpu_configurer.h"
#include "common/common.h"

#include "base/command_line.h"
#include "base/logging.h"
#include "base/strings/string_number_conversions.h"


namespace switches {
  // Set auto hotplug if the user knows, if not need to auto detect
  const char kAutoHotplug[] = "auto-hotplug";

  // Turn on or off the auto hotplug mechanism ("on" or "off")
  const char kSetAutoHotplug[] = "set-auto-hotplug";

  // Set number of online cores
  // Cores [0..num-cores-enabled - 1] will be set online
  const char kSetNumOnlineCores[] = "set-num-online-cores";

  // Set frequency governor
  const char kSetGovernor[] = "set-governor";

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

void PrintUsage(const char* program) {
  printf("Please provide options. Example on SM-G900H\n");
  printf("Example 1: %s --max-core-id=7 --auto-hotplug=dm-hotplug --set-auto-hotplug=off --set-num-online-cores=8 --set-governor=performance --max-freq=1900000\n", program);
  printf("Example 2: %s --max-core-id=7 --auto-hotplug=dm-hotplug --set-auto-hotplug=on --set-num-online-cores=8 --set-governor=interactive --max-freq=1900000 --min-freq=500000", program);
}

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
  if (argc == 1) {
    PrintUsage(argv[0]);
    return EXIT_FAILURE;
  }

  android_tools::Init(argc, argv);

  const base::CommandLine& cmdline = *base::CommandLine::ForCurrentProcess();

  // Default to 8 cores
  size_t max_core_id = kMaxNumCores - 1;
  if (cmdline.HasSwitch(switches::kMaxCoreId)) {
    if (!base::StringToUint(cmdline.GetSwitchValueASCII(switches::kMaxCoreId), &max_core_id)) {
      LOG(ERROR) << "Invalid option for " << switches::kMaxCoreId;
      return 1;
    }
  } else {
      LOG(WARNING) << "No max core id, use default max_core_id: " << max_core_id;
  }

  android_tools::CpuConfigurer cpu_configurer(max_core_id);

  // Disable hotplug daemon/mechanism
  // TODO: auto detect cpu management daemon and auto hotplug mechanism
  std::string auto_hotplug_option = cmdline.GetSwitchValueASCII(switches::kAutoHotplug);

  cpu_configurer.SetAutoHotplugType(auto_hotplug_option);

  std::string set_auto_hotplug_option = cmdline.GetSwitchValueASCII(switches::kSetAutoHotplug);
  // Always disable auto hotplug first
  // TODO: unify mpdecision and dm-hotplug size_to auto-hotplug
  if (!set_auto_hotplug_option.empty()) {
    if (set_auto_hotplug_option == switches::values::kOn || 
        set_auto_hotplug_option == switches::values::kOff) {
      cpu_configurer.SetAutoHotplugEnabled(false);
    } else {
      LOG(ERROR) << "Invalid values for set auto hotplug option: " << set_auto_hotplug_option;
    }
  }

  if (cmdline.HasSwitch(switches::kSetNumOnlineCores)) {
    size_t num_online_cores;
    if (!base::StringToUint(cmdline.GetSwitchValueASCII(switches::kSetNumOnlineCores), &num_online_cores)) {
      LOG(ERROR) << "Invalid option for " << switches::kSetNumOnlineCores << ": " << cmdline.GetSwitchValueASCII(switches::kSetNumOnlineCores);
      return 1;
    }
    cpu_configurer.SetNumOnlineCores(num_online_cores);
  }

  if (cmdline.HasSwitch(switches::kSetGovernor)) {
    cpu_configurer.SetGovernorForOnlineCores(cmdline.GetSwitchValueASCII(switches::kSetGovernor));
  }

  ;
  if (cmdline.HasSwitch(switches::kMaxFreq)) {
    cpu_configurer.SetMaxFreqForOnlineCores(cmdline.GetSwitchValueASCII(switches::kMaxFreq));
  }

  if (cmdline.HasSwitch(switches::kMinFreq)) {
    cpu_configurer.SetMinFreqForOnlineCores(cmdline.GetSwitchValueASCII(switches::kMinFreq));
  }

  // Enabled auto-hotplug if needed
  if (set_auto_hotplug_option == switches::values::kOn) {
    cpu_configurer.SetAutoHotplugEnabled(true);
  }

  return 0;
}
