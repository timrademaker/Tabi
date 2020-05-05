# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Tabi" LANGUAGES CXX)

# Set the C++ language standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set compiler options
if (MSVC)
     # Enable warning level 4 and treat all warnings as errors
    add_compile_options("/W4" "/WX")
else ()
	
endif ()


# Include sub-projects.
add_subdirectory ("Tabi")
add_subdirectory("Game")
