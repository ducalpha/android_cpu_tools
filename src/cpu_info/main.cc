// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "base/file_util.h"

#include "cpu_configurer.h"
#include "cpu_info.h"

namespace {
  const char kOutputFileName[] = "cpu-info-command-line";
};
// Populate cpu information, then write it to a file in command line form
int main(int argc, char **argv)
{
  CpuInfo cpu_info;
  size_t num_possible_cores = cpu_info.MaxCoreId() - cpu_info.MinCoreId() + 1;

  CpuConfigurer cpu_configurer;

  // TODO: save the auto hotplug state
  cpu_configurer.SetAutoHotplugEnabled(false);

  cpu_configurer.SetNumOnlineCores(num_possible_cores);

  cpu_info.PopulateClusterInfo();

  base::WriteToFile(kOutputFileName, cpu_info.ToChromeCommandLine());

  // TODO: restore the auto hotplug state
  cpu_configurer.SetAutoHotplugEnabled(true);

  return 0;
}
