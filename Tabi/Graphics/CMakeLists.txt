# CMakeList.txt : CMake project for Common
cmake_minimum_required (VERSION 3.8)

# Set headers for Graphics
set(HEADERS
    inc/IWindow.h
    inc/IRenderer.h
    inc/IContext.h
    inc/Windows/OpenGL/OpenGLWindow.h
    inc/Windows/OpenGL/OpenGLContext.h
    inc/Windows/OpenGL/OpenGLRenderer.h
    inc/Windows/OpenGL/OpenGLHelpers.h
)

# Set sources for Graphics
set(SOURCES
    src/IRenderer.cpp
    src/IWindow.cpp
    src/Windows/OpenGL/OpenGLWindow.cpp
    src/Windows/OpenGL/OpenGLContext.cpp
    src/Windows/OpenGL/OpenGLRenderer.cpp
    src/Windows/OpenGL/OpenGLHelpers.cpp
)

# Add source to this project's executable.
add_library(Graphics EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})


# Add third-party includes
set (GLAD_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/glad/)

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
#target_include_directories(Graphics PRIVATE ${GLAD_DIR}/include)

# Add libraries
target_link_libraries(Graphics PUBLIC TabiCommon Logger Core GLAD)