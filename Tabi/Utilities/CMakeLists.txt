# CMakeList.txt : CMake project for Utilities
cmake_minimum_required (VERSION 3.8)

# Set headers for ResourceManager
set(HEADERS
    inc/TabiUtilities.h
    inc/Delegate.h
)

# Set sources for Utilities
set(SOURCES
    src/TabiUtilities.cpp
)

# Add source to this project's executable.
add_library(Utilities ${SOURCES} ${HEADERS})


target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Utilities PUBLIC TabiCommon Logger)