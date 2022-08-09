# CMakeLists.txt: CMake project for imgui
cmake_minimum_required (VERSION 3.8)

# Set headers for imgui
set(HEADERS
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui_internal.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
)

# Set sources for imgui
set(SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)

# Add source to this project's library.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(imgui ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR})
