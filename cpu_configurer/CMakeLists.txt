cmake_minimum_required(VERSION 3.2)

project (cpu_configurer CXX)

include ("${CPU_CONFIGURER_SOURCE_DIR}/../cmake/SeparateBuild.cmake")

file (GLOB CPU_CONFIGURER_SRC "${CPU_CONFIGURER_SOURCE_DIR}/*.cc")

add_executable (cpu_configurer ${CPU_CONFIGURER_SRC})
