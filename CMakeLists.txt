cmake_minimum_required (VERSION 2.8)

project (AndroidTools)

set (CMAKE_MODULE_PATH cmake)

include_directories (${CMAKE_SOURCE_DIR}/lib)

add_subdirectory (lib)
add_subdirectory (src)


