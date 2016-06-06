// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

#include "cpu_configurer/cpu_configurer.h"
#include "cpu_info/cpu_info.h"
#include "common/common.h"

#include <iostream>

// Populate cpu information, then write it to a file in command line form
int main(int argc, char **argv) {
  android_cpu_tools::Init(argc, argv);

  android_cpu_tools::CpuInfo cpu_info;
  size_t num_possible_cores = cpu_info.MaxCoreId() - cpu_info.MinCoreId() + 1;

  android_cpu_tools::CpuConfigurer cpu_configurer(cpu_info.MaxCoreId());

  // TODO: save the auto hotplug state
  cpu_configurer.SetAutoHotplugEnabled(false);

  cpu_configurer.SetNumOnlineCores(num_possible_cores);

  cpu_info.PopulateClusterInfo();

  std::string chrome_cmdline = cpu_info.ToChromeCommandLine();
  std::cout << chrome_cmdline;

  // TODO: restore the auto hotplug state
  cpu_configurer.SetAutoHotplugEnabled(true);

  return 0;
}
