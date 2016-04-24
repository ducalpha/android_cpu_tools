// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_
#define ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace android_tools {
class AutoHotplug {
 public:
  virtual void SetEnabled(bool enabled) = 0;

  // Create a new auto hotplug
  // If type is recognized, call Auto detect
  static std::unique_ptr<AutoHotplug> Create(std::string type);
  static std::vector<std::string> SupportedTypes();
  // Detect the auto hotplug mechanism
  static std::unique_ptr<AutoHotplug> AutoDetectCreate();

 private:
  std::map<std::string, std::function<std::unique_ptr<AutoHotplug>()>> creation_map_{
    { "mpdecision", []() { return std::unique_ptr<AutoHotplug>(new Mpdecision()); } },
    { "dm-hotplug", []() { return std::unique_ptr<AutoHotplug>(new DmHotplug()); } },
  };
};

class Mpdecision : public AutoHotplugMechanism {
  virtual void SetEnabled(bool enabled) override;
};

class DmHotplug : public AutoHotplugMechanism {
  virtual void SetEnabled(bool enabled) override;
};

}  // namespace android_tools

#endif  // ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_
