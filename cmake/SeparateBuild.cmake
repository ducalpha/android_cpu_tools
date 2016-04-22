option (SEPARATE_BUILD "Perform a standalone/separate build" OFF)

if (SEPARATE_BUILD)
  if (SEPARATE_BUILD STREQUAL "ON")
    set (LIBRARY_DIR "${CMAKE_SOURCE_DIR}/../lib/")
  else()
    set (LIBRARY_DIR "${SEPARATE_BUILD}")
  endif()
  include_directories (${LIBRARY_DIR})
  # add_subdirectory (${LIBRARY_DIR})
endif (SEPARATE_BUILD)

