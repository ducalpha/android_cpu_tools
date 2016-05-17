project (CPU_INFO CXX)

set (SRC ${CPU_INFO_SOURCE_DIR}/cpu_info.cc ${CPU_INFO_SOURCE_DIR}/cpu_info_switches.cc)

set (CPU_INFO_SRC ${SRC} ${CPU_INFO_SOURCE_DIR}/main.cc)

set (CPU_INFO_TEST_SRC ${SRC} ${CPU_INFO_SOURCE_DIR}/test_main.cc)

add_executable (cpu_info ${CPU_INFO_SRC})
target_link_libraries (cpu_info libcpu_configurer base_chromium)

add_executable (cpu_info_test ${CPU_INFO_TEST_SRC})
target_link_libraries (cpu_info_test libcpu_configurer base_chromium)
