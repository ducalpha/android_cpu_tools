// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include <string>

#include "base/command_line.h"
#include "base/logging.h"
#include "base/strings/string_split.h"

int main(int argc, char **argv) {
  base::CommandLine cmdline(argc, argv);

  std::string args = " --cpu-core-ids=0-7 --cluster-core-ids=0-3,4-7 --cluster-freqs=500000-1300000,800000-1900000 --cluster-freq-governors=interactive,interactive";
  std::vector<std::string> another_argv = base::SplitString(args, " ", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);

  cmdline.AppendArguments(base::CommandLine(another_argv), false);

  LOG(INFO) << "Combined command line: " << cmdline.GetCommandLineString();
  return 0;
}
