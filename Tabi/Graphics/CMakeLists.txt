# CMakeList.txt : CMake project for Common
cmake_minimum_required (VERSION 3.8)

# Set headers for Graphics
set(HEADERS
    inc/IWindow.h
    inc/IRenderer.h
)

# Set sources for Logger
set(SOURCES
    src/IRenderer.cpp
)

# Add source to this project's executable.
add_library(Graphics EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Graphics PUBLIC TabiCommon)