// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include <memory>

#include "base/file_util.h"
#include "cpu_configurer/auto_hotplug.h"

namespace {

const char[] kMpdecisionPath = "/system/bin/mpdecision";
const char[] kEnabledDmHotplugPath = "/sys/power/enable_dm_hotplug";

}  // namespace

namespace android_tools {

std::unique_ptr<AutoHotplug> AutoHotplug::Create(Type type) {
  switch (type) {
    case AutoHotplugMechanism::MPDECISION:
      return std::unique_ptr<AutoHotplug>(new Mpdecision());
      break;
    case AutoHotplugMechanism::DM_HOTPLUG:
      return std::unique_ptr<AutoHotplug>(new DmHotplug());
      break;
    default:
      LOG(ERROR) << "Unknown type " << type;
  }
  return nullptr;
}

std::unique_ptr<AutoHotplug> AutoHotplug::CreateAutoDetect() {
  return Create(AutoDetect());
}

Type AutoHotplug::AutoDetect() {
  if (FileUtil::PathExists(kMpdecisionPath)) {
    return Type::MPDECISION;
  } else if (FileUtil::PathExists(kEnabledDmHotplugPath)) {
    return Type::DM_HOTPLUG;
  }

  return Type::UNKNOWN;
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
