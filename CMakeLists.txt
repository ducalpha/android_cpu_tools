cmake_minimum_required (VERSION 2.8)

project (AndroidTools)

include_directories (${CMAKE_SOURCE_DIR}/lib)
add_subdirectory (lib)
add_subdirectory (cpu_configurer)
add_subdirectory (workload_generator)
