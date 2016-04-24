file (GLOB BASE_SRC 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" 
  "${CMAKE_CURRENT_SOURCE_DIR}/threading/*.cc" 
  "${CMAKE_CURRENT_SOURCE_DIR}/files/*.cc" 
  "${CMAKE_CURRENT_SOURCE_DIR}/posix/*.cc")

add_library (base ${BASE_SRC})
target_link_libraries (base log)
