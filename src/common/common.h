// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)


#ifndef ANDROID_TOOLS_COMMON_COMMON_H_
#define ANDROID_TOOLS_COMMON_COMMON_H_

#include "base/command_line.h"
#include "base/logging.h"

// This file contains common routines for android_tools

namespace android_tools {

void Init(int argc, char **argv) {
  base::CommandLine::Init(argc, argv);
  logging::LoggingSettings settings;
  logging::InitLogging(settings);
}


}  // namespace android_tools

#endif  // ANDROID_TOOLS_COMMON_COMMON_H_