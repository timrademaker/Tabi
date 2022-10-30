# CMakeLists.txt: CMake project for FileSystem
cmake_minimum_required (VERSION 3.8)

# Set headers for FileSystem
set(HEADERS
    inc/IFile.h
)

# Set sources for FileSystem
set(SOURCES
    src/IFile.cpp
)

if(WIN32)
    list(APPEND HEADERS 
        inc/Windows/FileWindows.h
    )
    
    list(APPEND SOURCES
        src/Windows/FileWindows.cpp
    )
endif()

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(FileSystem EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(FileSystem PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(FileSystem PUBLIC TabiCommon Logger)