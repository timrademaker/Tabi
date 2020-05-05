# CMakeList.txt : CMake project for Common
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library(TabiCommon INTERFACE)

target_include_directories(TabiCommon INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
