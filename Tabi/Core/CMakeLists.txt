# CMakeList.txt : CMake project for Core
cmake_minimum_required (VERSION 3.8)

# Set headers for Core
set(HEADERS 
    inc/Application.h
    inc/GameBase.h
)

# Set sources for Core
set(SOURCES 
    src/Application.cpp
)

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(Core EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
# PUBLIC: Used in headers and source files
target_link_libraries(Core PUBLIC TabiCommon Graphics Renderer)
# PRIVATE: Used in source files
target_link_libraries(Core PRIVATE Logger Input)

add_custom_command(
    TARGET Core
    POST_BUILD
    COMMAND xcopy \"${CMAKE_CURRENT_LIST_DIR}/../../TabiAssets\" \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TabiAssets\" /S /Y /I /C
)
