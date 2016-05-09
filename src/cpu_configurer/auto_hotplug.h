// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_
#define ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_

#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace android_cpu_tools {
class AutoHotplug {
 public:
  AutoHotplug(const std::string& name);

  virtual void SetEnabled(bool enabled) = 0;

  // return a name for cpu-configurer
  std::string Name() const {
    return name_;
  }

  // Create a new auto hotplug
  // If type is recognized, call Auto detect
  static std::unique_ptr<AutoHotplug> Create(std::string type);
  static std::vector<std::string> SupportedTypes();
  // Detect the auto hotplug mechanism
  static std::unique_ptr<AutoHotplug> AutoDetectCreate();

 private:
  std::string name_;
};

class Mpdecision : public AutoHotplug {
 public:
  Mpdecision(const std::string& name);
  virtual void SetEnabled(bool enabled) override;
};

class DmHotplug : public AutoHotplug {
 public:
  DmHotplug(const std::string& name);
  virtual void SetEnabled(bool enabled) override;
};

}  // namespace android_cpu_tools

#endif  // ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_
