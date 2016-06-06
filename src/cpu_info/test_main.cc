// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

#include <string>

#include "base/command_line.h"
#include "base/logging.h"
#include "base/strings/string_split.h"
#include "cpu_info/cpu_info.h"

int main(int argc, char **argv) {
  base::CommandLine cmdline(argc, argv);

  std::string args = "chrome --auto-hotplug=dm-hotplug --cpu-core-ids=0-7 --cluster-core-ids=0-3,4-7 --cluster-freqs=500000-1300000,800000-1900000 --cluster-freq-governors=interactive,interactive";
  std::vector<std::string> another_argv = base::SplitString(args, " ", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

  for (const auto& arg : another_argv) {
    LOG(INFO) << arg;
  }
  cmdline.AppendArguments(base::CommandLine(another_argv), false);

  android_cpu_tools::CpuInfo cpu_info;
  //cpu_info.InitializeFromCommandLine(cmdline);

  //LOG(INFO) << cpu_info.AutoHotplug();
  return 0;
}
