# CMakeList.txt : CMake project for Graphics
cmake_minimum_required (VERSION 3.8)

# Set headers for Graphics
set(HEADERS
    inc/Camera.h
    inc/Graphics.h
    inc/Light.h
    inc/IWindow.h
)

# Set sources for Graphics
set(SOURCES
    src/Camera.cpp
    src/Graphics.cpp
    src/IWindow.cpp
)

if(WIN32)
    list(APPEND HEADERS 
        inc/Windows/WindowsWindow.h
    )
    
    list(APPEND SOURCES
        src/Windows/WindowsWindow.cpp
    )
endif()

# Add source to this project's executable.
add_library(Graphics EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Graphics PUBLIC TabiCommon Logger Core FileSystem ResourceManager Renderer)
