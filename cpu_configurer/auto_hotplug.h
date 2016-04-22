// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#ifndef ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_
#define ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_

namespace android_tools {
class AutoHotplug {

  enum class Type : int {
    UNKNOWN,
    MPDECISION, // used on Qualcomm Snapdragon smartphones
    DM_HOTPLUG  // used on Samsung Exynos smartphones
  };

  virtual void SetEnabled(bool enabled) = 0;

  // Detect the auto hotplug mechanism
  Type DetectAutoHotplugMechanism();
};

class Mpdecision : public AutoHotplugMechanism {
  virtual void SetEnabled(bool enabled);
};

class DmHotplug : public AutoHotplugMechanism {
  virtual void SetEnabled(bool enabled);
};

}  // namespace android_tools

#endif  // ANDROID_TOOLS_CPU_CONFIGURER_AUTO_HOTPLUG_H_
