// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)


#ifndef ANDROID_CPU_TOOLS_COMMON_COMMON_H_
#define ANDROID_CPU_TOOLS_COMMON_COMMON_H_

#include "base/command_line.h"
#include "base/logging.h"

// This file contains common routines for android_tools

namespace android_cpu_tools {

void Init(int argc, char **argv) {
  base::CommandLine::Init(argc, argv);
  logging::LoggingSettings settings;
  logging::InitLogging(settings);
}


}  // namespace android_cpu_tools

#endif  // ANDROID_CPU_TOOLS_COMMON_COMMON_H_
