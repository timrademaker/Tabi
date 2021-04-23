# CMakeList.txt : CMake project for Collision
cmake_minimum_required (VERSION 3.8)

# Set headers for Collision
set(HEADERS 
    inc/GJK.h
    inc/Simplex.h

    inc/Colliders/ICollider.h
    inc/Colliders/Sphere.h
    inc/Colliders/Hull.h
)

# Set sources for Collision
set(SOURCES 
    src/GJK.cpp
    src/Simplex.cpp

    src/Colliders/ICollider.cpp
    src/Colliders/Sphere.cpp
    src/Colliders/Hull.cpp
)

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(Collision EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(Collision PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
# PUBLIC: Used in headers and source files
target_link_libraries(Collision PUBLIC TabiCommon Math)
# PRIVATE: Used in source files
target_link_libraries(Collision PRIVATE Logger)

