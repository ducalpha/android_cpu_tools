// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include <string>

#include "base/command_line.h"
#include "base/logging.h"

int main(int argc, char **argv) {
  base::CommandLine cmdline(argc, argv);
  LOG(INFO) << cmdline.GetSwitchValueASCII("cluster-info");
  return 0;
}
