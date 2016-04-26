project (CPU_INFO CXX)

file (GLOB CPU_INFO_SRC "${CPU_INFO_SOURCE_DIR}/*.cc")

add_executable (cpu_info ${CPU_INFO_SRC})
target_link_libraries (cpu_info libcpu_configurer base)
