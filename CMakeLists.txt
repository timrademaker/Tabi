# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Tabi" LANGUAGES CXX)

# Set the C++ language standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}/lib")

# Set compiler options
if (MSVC)
     # Enable warning level 4 and treat all warnings as errors
    add_compile_options("/W4" "/WX")
else ()
	
endif ()

if(USE_OPENGL)
    add_compile_definitions("OPENGL")
endif()

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
add_compile_definitions("TINYGLTF_IMPLEMENTATION" "STB_IMAGE_IMPLEMENTATION" "STB_IMAGE_WRITE_IMPLEMENTATION")


# Include sub-projects.
add_subdirectory ("Tabi")
add_subdirectory("Game")
add_subdirectory("ThirdParty")

# Copy assets to output directory
file(COPY "Assets" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})