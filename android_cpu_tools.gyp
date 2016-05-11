# Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
# Licensed under MIT ($DUC_LICENSE_URL)

{
  'targets': [
    {
      'target_name': 'android_cpu_tools_cpu_control',
      'type': 'static_library',
      'toolsets': ['host', 'target'],
      'include_dirs': [
        '../../../',
        'src'
      ],
      'sources': [
        'src/common/common.h',
        'src/cpu_configurer/auto_hotplug.cc',
        'src/cpu_configurer/auto_hotplug.h',
        'src/cpu_configurer/cpu_configurer_switches.cc',
        'src/cpu_configurer/cpu_configurer_switches.h',
        'src/cpu_info/cpu_info.cc',
        'src/cpu_info/cpu_info.h',
        'src/cpu_info/cpu_info_switches.cc',
        'src/cpu_info/cpu_info_switches.h',
      ],
    },
    {
      'target_name': 'android_cpu_tools_switches',
      'type': 'static_library',
      'toolsets': ['host', 'target'],
      'include_dirs': [
        '../../../',
        'src'
      ],
      'sources': [
        'src/cpu_configurer/cpu_configurer_switches.cc',
        'src/cpu_configurer/cpu_configurer_switches.h',
        'src/cpu_info/cpu_info_switches.cc',
        'src/cpu_info/cpu_info_switches.h',
      ],
    },
    {
      'target_name': 'android_cpu_tools_workload_generator',
      'type': 'static_library',
      'toolsets': ['host', 'target'],
      'include_dirs': [
        '../../../',
        'src'
      ],
      'sources': [
        'src/workload_generator/workload_generator.cc',
        'src/workload_generator/workload_generator.h',
      ],
    },
  ],
}

