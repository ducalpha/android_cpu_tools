// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "cpu_info/cpu_info_switches.h"

namespace switches {

// Set auto hotplug if the user knows, if not need to auto detect
// TODO: avoid conflict with cpu-info auto-hotplug
const char kAutoHotplugType[] = "auto-hotplug-type";

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

// Turn on/off values
const char kOn[] = "on";

const char kOff[] = "off";
}

}  // namespace switches
