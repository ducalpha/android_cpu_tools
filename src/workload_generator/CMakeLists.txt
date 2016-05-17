project (WORKLOAD_GENERATOR CXX)

file (GLOB WORKLOAD_GENERATOR_SRC "${WORKLOAD_GENERATOR_SOURCE_DIR}/*.cc")

add_executable (workload_generator ${WORKLOAD_GENERATOR_SRC})
target_link_libraries (workload_generator base_chromium)
