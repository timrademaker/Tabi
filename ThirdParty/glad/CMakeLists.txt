# CMakeLists.txt: CMake project for GLAD
cmake_minimum_required (VERSION 3.8)

project(GLAD_P)

# Set headers for GLAD
set(HEADERS
    include/glad/gl.h
    include/glad/wgl.h
    include/KHR/khrplatform.h
)

# Set sources for GLAD
set(SOURCES
    src/gl.c
    src/wgl.c
)

# Add source to this project's library.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(GLAD ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
