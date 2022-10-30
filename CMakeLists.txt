# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Tabi" LANGUAGES CXX)

# Set the C++ language standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}/bin")
else()
    set(NO_TABI_EXAMPLE_GAME True)  # If CMAKE_RUNTIME_OUTPUT_DIRECTORY is set, we simply assume the project is used as a submodule
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}/lib")
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}/lib")
endif()

# Set compiler options
if (MSVC)
     # Enable warning level 4
    add_compile_options("/W4")
else ()
	
endif ()

if(WIN32)
    set(USE_OPENGL True)
    add_compile_definitions("OPENGL")
    add_compile_definitions(MINIMUM_OGL_VERSION_MAJOR=4)
    add_compile_definitions(MINIMUM_OGL_VERSION_MINOR=5)
endif()

# Include sub-projects.
add_subdirectory("Tabi")
add_subdirectory("ThirdParty")

if (NOT NO_TABI_EXAMPLE_GAME)
    add_subdirectory("Game")
endif()

include(CTest)

if(BUILD_TESTING)
    add_subdirectory(./UnitTests)
endif(BUILD_TESTING)
