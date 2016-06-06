// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

#include "cpu_configurer/auto_hotplug.h"

#include <string>
#include <vector>

#include "base/command_line.h"
#include "base/logging.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/process/launch.h"

namespace {

const std::string kMpdecisionPath = "/system/bin/mpdecision";
const std::string kEnabledDmHotplugPath = "/sys/power/enable_dm_hotplug";

const std::string kMpdecision = "mpdecision";
const std::string kDmHotplug = "dm-hotplug";

std::map<std::string, std::function<std::unique_ptr<android_cpu_tools::AutoHotplug>(const std::string&)>> creation_map{
  { kMpdecision, [](const std::string& name) { return std::unique_ptr<android_cpu_tools::AutoHotplug>(new android_cpu_tools::Mpdecision(name)); } },
  { kDmHotplug, [](const std::string& name) { return std::unique_ptr<android_cpu_tools::AutoHotplug>(new android_cpu_tools::DmHotplug(name)); } },
};

}  // namespace

namespace android_cpu_tools {

// static
std::unique_ptr<AutoHotplug> AutoHotplug::Create(std::string type) {
  auto creation_type = creation_map.find(type);
  if (creation_type != creation_map.end()) {
    return (creation_type->second)(type);
  } else {
    std::string supported_types;
    for (const auto& m : creation_map) {
      supported_types.append(m.first + " ");
    }
    LOG(WARNING) << "Auto hotplug type is not recognized (supported types: " 
        << supported_types << "); auto detect";
    return AutoDetectCreate();
  }
  return nullptr;
}

// static
std::unique_ptr<AutoHotplug> AutoHotplug::AutoDetectCreate() {
  if (base::PathExists(base::FilePath(kMpdecisionPath))) {
    VLOG(1) << "Detected mpdecision";
    return creation_map[kMpdecision](kMpdecision);
  } else if (base::PathExists(base::FilePath(kEnabledDmHotplugPath))) {
    VLOG(1) << "Detected dm hotplug";
    return creation_map[kDmHotplug](kDmHotplug);
  } else {
    LOG(ERROR) << "Cannot detect the auto hotplug mechanism";
  }

  return nullptr;
}

AutoHotplug::AutoHotplug(const std::string& name)
  : name_(name) {
}

Mpdecision::Mpdecision(const std::string& name)
  : AutoHotplug(name) {
}

DmHotplug::DmHotplug(const std::string& name)
  : AutoHotplug(name) {
}

void Mpdecision::SetEnabled(bool enabled) {
  std::vector<std::string> cmd_argv{"su", "-c"};
  cmd_argv.emplace_back(enabled ? "start" : "stop");
  cmd_argv.emplace_back(kMpdecision);
  base::CommandLine cmd(cmd_argv);
  base::Process process = base::LaunchProcess(cmd, base::LaunchOptions());
  if (!process.IsValid()) {
    LOG(ERROR) << "Cannot run cmd " << cmd.GetCommandLineString();
    return;
  }

  int exit_code;
  if (!process.WaitForExit(&exit_code)) {
    LOG(ERROR) << "Cannot get return code for cmd " << cmd.GetCommandLineString();
    return;
  }
  if (exit_code != 0)
    LOG(ERROR) << "Running " << cmd.GetCommandLineString() << " failed with code " << exit_code;

  // to save time, skip checking mpdecision processes
}

void DmHotplug::SetEnabled(bool enabled) {
  base::WriteFile(base::FilePath("/sys/power/enable_dm_hotplug"), enabled ? "1" : "0", 1);
}

}  // namespace android_cpu_tools
