cmake_minimum_required (VERSION 3.2)

project (ANDROID_TOOLS CXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/cmake/android-cmake")
# set (CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/android-cmake/android.toolchain.cmake")

# message (${ANDROID_NATIVE_API_LEVEL})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -s")
# include (android.toolchain)

# ducalpha: workaround the UINT64_C compilation error on Android-16
add_definitions (-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG)

include_directories (${CMAKE_SOURCE_DIR}/lib/chromium ${CMAKE_SOURCE_DIR}/src)

add_subdirectory (lib)
add_subdirectory (src)
add_subdirectory (test)
