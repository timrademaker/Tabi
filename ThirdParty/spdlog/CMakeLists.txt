# Minimum CMake version
cmake_minimum_required (VERSION 3.8)

# Create library for spdlog
add_library(spdlog INTERFACE)

# Add include directories
target_include_directories(spdlog INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Generated on 2020-06-20 17:08