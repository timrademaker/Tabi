# CMakeList.txt : CMake project for Graphics
cmake_minimum_required (VERSION 3.8)

# Set headers for Graphics
set(HEADERS
    inc/Camera.h
    inc/Light.h
    inc/IWindow.h
    inc/IRenderer.h
    inc/IContext.h
    inc/Windows/WindowsWindow.h
    inc/Windows/OpenGL/OpenGLContext.h
    inc/Windows/OpenGL/OpenGLRenderer.h
    inc/Windows/OpenGL/OpenGLHelpers.h
)

# Set sources for Graphics
set(SOURCES
    src/IRenderer.cpp
    src/IWindow.cpp
    src/Windows/WindowsWindow.cpp
    src/Windows/OpenGL/OpenGLContext.cpp
    src/Windows/OpenGL/OpenGLRenderer.cpp
    src/Windows/OpenGL/OpenGLHelpers.cpp
)

# Add source to this project's executable.
add_library(Graphics EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Graphics PUBLIC TabiCommon Logger Core GLAD FileSystem ResourceManager)