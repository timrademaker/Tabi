# CMakeList.txt : CMake project for Math
cmake_minimum_required (VERSION 3.8)

# Set headers for ResourceManager
set(HEADERS
    inc/Math/vec2.h
    inc/Math/vec3.h
    inc/Math/vec4.h
    inc/Math/mat4.h
    inc/Math/TabiMath.h
)

# Set sources for Math
set(SOURCES
    src/Math/vec2.cpp
    src/Math/vec3.cpp
    src/Math/vec4.cpp
    src/Math/mat4.cpp
    src/Math/TabiMath.cpp
)

# Add source to this project's executable.
add_library(Math ${SOURCES} ${HEADERS})


target_include_directories(Math PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)


target_link_libraries(Math PUBLIC TabiCommon Logger)