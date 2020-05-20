# CMakeList.txt : CMake project for ResourceManager
cmake_minimum_required (VERSION 3.8)

# Set headers for ResourceManager
set(HEADERS
    inc/IResource.h
    inc/ResourceManager.h
    inc/Resources/Material.h
    inc/Resources/Mesh.h
    inc/Resources/Model.h
    inc/Resources/Texture.h
    inc/ModelLoaderUtils.h
)

# Set sources for ResourceManager
set(SOURCES
    src/ResourceManager.cpp
    src/Resources/Material.cpp
    src/Resources/Mesh.cpp
    src/Resources/Model.cpp
    src/Resources/Texture.cpp
    src/ModelLoaderUtils.cpp
)

# Add source to this project's executable.
add_library(ResourceManager EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

target_include_directories(ResourceManager PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(ResourceManager PUBLIC TabiCommon Graphics Utilities TinyGLTF)