# CMakeList.txt : CMake project for tinygltf
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library(TinyGLTF INTERFACE)

target_include_directories(TinyGLTF INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
