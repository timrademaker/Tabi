# CMakeList.txt : CMake project for Math
cmake_minimum_required (VERSION 3.8)

# Set headers for ResourceManager
set(HEADERS
    inc/vec2.h
    inc/vec3.h
    inc/vec4.h
    inc/mat4.h
)

# Set sources for Math
set(SOURCES
    src/vec2.cpp
    src/vec3.cpp
    src/vec4.cpp
)

# Add source to this project's executable.
add_library(Math ${SOURCES} ${HEADERS})


target_include_directories(Math PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)


target_link_libraries(Math PUBLIC TabiCommon Logger)