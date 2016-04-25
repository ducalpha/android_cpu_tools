// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "cpu_configurer/auto_hotplug.h"

#include "base/logging.h"
#include "base/files/file_util.h"

namespace {

const char kMpdecisionPath[] = "/system/bin/mpdecision";
const char kEnabledDmHotplugPath[] = "/sys/power/enable_dm_hotplug";

}  // namespace

namespace android_tools {

// static
std::unique_ptr<AutoHotplug> AutoHotplug::Create(std::string type) {
  auto creation_type = creation_map_.find(type);
  if (creation_type != creation_map_.end()) {
    return (creation_type->second)();
  } else {
    std::string supported_types;
    for (const auto& m : creation_map_) {
      supported_types.append(m.first + " ");
    }
    LOG(ERROR) << "Auto hotplug type is not recognized (supported types: " 
        << supported_types << "\n; auto detect and create";
    return AutoDetectCreate();
  }
  return nullptr;
}

// static
std::unique_ptr<AutoHotplug> AutoHotplug::AutoDetectCreate() {
  if (base::PathExists(kMpdecisionPath)) {
    return creation_map_["mpdecision"]();
  } else if (base::PathExists(kEnabledDmHotplugPath)) {
    return creation_map_["dm-hotplug"]();
  } else {
    LOG(ERROR) << "Cannot detect the auto hotplug mechanism";
  }

  return nullptr;
}

// static
std::vector<std::string> AutoHotplug::SupportedTypes() {
}

void Mpdecision::SetEnabled(bool enabled) {
  std::string cmd = "su -c ";
  cmd += enabled ? "start" : "stop";
  cmd += " mpdecision";
  std::system(cmd.c_str());
  // to save time, skip checking mpdecision processes
}

void DmHotplug::SetEnabled(bool enabled) {
  base::WriteFile("/sys/power/enable_dm_hotplug", enabled ? "1" : "0", 1);
}

}  // namespace android_tools
