// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "cpu_configurer/cpu_configurer.h"
#include "cpu_info/cpu_info.h"

#include "base/files/file_util.h"

namespace {
  const char kOutputFileName[] = "cpu-info-command-line";
};

// Populate cpu information, then write it to a file in command line form
int main(int argc, char **argv)
{
  android_tools::CpuInfo cpu_info;
  size_t num_possible_cores = cpu_info.MaxCoreId() - cpu_info.MinCoreId() + 1;

  android_tools::CpuConfigurer cpu_configurer;

  // TODO: save the auto hotplug state
  cpu_configurer.SetAutoHotplugEnabled(false);

  cpu_configurer.SetNumOnlineCores(num_possible_cores);

  cpu_info.PopulateClusterInfo();

  std::string chrome_cmdline = cpu_info.ToChromeCommandLine();
  base::WriteFile(base::FilePath(kOutputFileName), chrome_cmdline.c_str(), chrome_cmdline.length());

  // TODO: restore the auto hotplug state
  cpu_configurer.SetAutoHotplugEnabled(true);

  return 0;
}
