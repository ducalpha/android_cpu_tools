# Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
# Licensed under MIT (https://github.com/ducalpha/android_cpu_tools/blob/master/LICENSE)

{
  'targets': [
    {
      'target_name': 'cpu_info',
      'type': 'static_library',
      'toolsets': ['host', 'target'],
      'include_dirs': [
        '../../../',
        'src'
      ],
      'sources': [
        'src/cpu_configurer/cpu_configurer_switches.cc',
        'src/cpu_configurer/cpu_configurer_switches.h',
        'src/cpu_info/command_line_cpu_info.cc',
        'src/cpu_info/cpu_info.h',
        'src/cpu_info/cpu_info_switches.cc',
        'src/cpu_info/cpu_info_switches.h',
      ],
    },
    {
      'target_name': 'workload_generator',
      'type': 'static_library',
      'toolsets': ['host', 'target'],
      'include_dirs': [
        '../../../',
        'src'
      ],
      'sources': [
        'src/workload_generator/platform_thread_assisted_scheduling_android.cc',
        'src/workload_generator/platform_thread.h',
        'src/workload_generator/workload_generator.cc',
        'src/workload_generator/workload_generator.h',
      ],
    },
  ],
}

