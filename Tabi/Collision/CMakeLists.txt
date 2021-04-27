# CMakeList.txt : CMake project for Collision
cmake_minimum_required (VERSION 3.8)

# Set headers for Collision
set(HEADERS 
    inc/GJK.h
    inc/ThreeSimplex.h

    inc/Colliders/Box.h
    inc/Colliders/Hull.h
    inc/Colliders/ICollider.h
    inc/Colliders/Sphere.h

    inc/ECS/ColliderComponent.h
    inc/ECS/CollisionSystem.h
)

# Set sources for Collision
set(SOURCES 
    src/GJK.cpp
    src/ThreeSimplex.cpp

    src/Colliders/Box.cpp
    src/Colliders/Hull.cpp
    src/Colliders/ICollider.cpp
    src/Colliders/Sphere.cpp

    src/ECS/ColliderComponent.cpp
    src/ECS/CollisionSystem.cpp
)

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(Collision EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(Collision PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
# PUBLIC: Used in headers and source files
target_link_libraries(Collision PUBLIC TabiCommon Math ECS Utilities)
