// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include "cpu_configurer/auto_hotplug.h"

#include "base/file_util.h"

namespace {

const char[] kMpdecisionPath = "/system/bin/mpdecision";
const char[] kEnabledDmHotplugPath = "/sys/power/enable_dm_hotplug";

}  // namespace

namespace android_tools {

// static
std::unique_ptr<AutoHotplug> AutoHotplug::Create(std::string type) {
  auto creation_type = creation_map.find(type);
  if (creation_type != creation_map.end()) {
    return (*create_type->second)();
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
  if (FileUtil::PathExists(kMpdecisionPath)) {
    return creation_map["mpdecision"]();
  } else if (FileUtil::PathExists(kEnabledDmHotplugPath)) {
    return creation_map["dm-hotplug"]();
  } else {
    LOG(ERROR) << "Cannot detect the auto hotplug mechanism";
  }

  return nullptr;
}

// static
std::vector<std::string> AutoHotplug::SupportedTypes() {
}

void Mpdecision::SetEnabled(bool enabled) {
  std::std::string cmd = "su -c ";
  cmd += enabled ? "start" : "stop";
  cmd += " mpdecision";
  std::system(cmd.c_str());
  // to save time, skip checking mpdecision processes
}

void DmHotplug:SetEnabled(bool enabled) {
  WriteString("/sys/power/enable_dm_hotplug", enabled ? "1" : "0");
}

}  // namespace android_tools
