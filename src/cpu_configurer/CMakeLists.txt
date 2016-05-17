project (CPU_CONFIGURER CXX)

set (CPU_CONFIGURER_LIB_SRC ${CPU_CONFIGURER_SOURCE_DIR}/cpu_configurer.cc ${CPU_CONFIGURER_SOURCE_DIR}/cpu_configurer_switches.cc ${CPU_CONFIGURER_SOURCE_DIR}/auto_hotplug.cc)

set (CPU_CONFIGURER_SRC ${CPU_CONFIGURER_LIB_SRC} "${CPU_CONFIGURER_SOURCE_DIR}/main.cc")

add_executable (cpu_configurer ${CPU_CONFIGURER_SRC})
target_link_libraries (cpu_configurer base_chromium)

add_library (libcpu_configurer ${CPU_CONFIGURER_LIB_SRC})
