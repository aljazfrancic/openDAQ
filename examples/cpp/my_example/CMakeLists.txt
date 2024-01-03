cmake_minimum_required(VERSION 3.20)
project(my_example VERSION ${OPENDAQ_EXAMPLES_VERSION})

find_package(openDAQ)
add_compile_definitions(MODULE_PATH="${OPENDAQ_MODULES_DIR}")

add_executable(my_example my_example.cpp)
target_link_libraries(my_example PRIVATE daq::opendaq)