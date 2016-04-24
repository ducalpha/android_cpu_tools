cmake_minimum_required (VERSION 3.2)

project (AndroidTools)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/cmake/android-cmake")
# set (CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/android-cmake/android.toolchain.cmake")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
# include (android.toolchain)


include_directories (${CMAKE_SOURCE_DIR}/lib)

add_subdirectory (lib)
# add_subdirectory (src)
add_subdirectory (tests)


