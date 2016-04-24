cmake_minimum_required(VERSION 3.2)

file (GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_executable (test_command_line ${SRC_FILES})
target_link_libraries(test_command_line base)
