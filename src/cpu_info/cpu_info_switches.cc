// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "cpu_info/cpu_info_switches.h"

// Use namespace switches which matches with Chrome to detect conflicts
namespace switches {

const char kCpuCoreIds[] = "cpu-core-ids";

const char kClusterCoreIds[] = "cluster-core-ids";

const char kClusterFreqs[] = "cluster-freqs";

const char kClusterFreqGovernors[] = "cluster-freq-governors";

// Name of auto-hotplug (mpdecision or dm-hotplug)
const char kAutoHotplug[] = "auto-hotplug";

}  // namespace switches
