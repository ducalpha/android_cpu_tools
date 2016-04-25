project (CPU_CONFIGURER CXX)

file (GLOB CPU_CONFIGURER_SRC "${CPU_CONFIGURER_SOURCE_DIR}/*.cc")

add_executable (cpu_configurer ${CPU_CONFIGURER_SRC})
