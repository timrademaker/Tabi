# CMakeLists.txt: CMake project for Input
cmake_minimum_required (VERSION 3.8)

# Set headers for Input
set(HEADERS
    inc/IInput.h
    inc/MouseButtons.h
)

# Set sources for Input
set(SOURCES
    # src/IInput.cpp
    src/MouseButtons.cpp
)

if(WINDOWS)
    list(APPEND HEADERS 
        #inc/Windows/WindowsInput.h
    )
    
    list(APPEND SOURCES
        #src/Windows/FileWindows.cpp
    )
endif()

if(ORBIS)

    
endif()

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(Input EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(Input PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Input PUBLIC TabiCommon Logger)