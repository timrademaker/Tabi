# CMakeLists.txt: CMake project for ECS
cmake_minimum_required (VERSION 3.8)

# Set headers for ECS
set(HEADERS
    inc/Entity.h
    inc/EntityManager.h
)

# Set sources for ECS
set(SOURCES
    
)

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(ECS EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(ECS PUBLIC TabiCommon Logger)