# CMakeList.txt : CMake project for ResourceManager
cmake_minimum_required (VERSION 3.8)

# Set headers for ResourceManager
set(HEADERS
    inc/IResource.h
    inc/ResourceManager.h
)

# Set sources for ResourceManager
set(SOURCES
    src/ResourceManager.cpp
)

# Add source to this project's executable.
add_library(ResourceManager EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})


target_include_directories(ResourceManager PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(ResourceManager PUBLIC Common Graphics Utilities)