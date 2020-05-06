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
elseif("${BUILD_PLATFORM}" STREQUAL "ORBIS")
    #PS4_ROOT and PS4_SDK
    message("Compiling for ORBIS")

    # Get PS4 SDK directory
    if(EXISTS "$ENV{SCE_ROOT_DIR}" AND IS_DIRECTORY "$ENV{SCE_ROOT_DIR}")
        string(REGEX REPLACE "\\\\" "/" PS4_ROOT $ENV{SCE_ROOT_DIR})
	    string(REGEX REPLACE "//" "/" PS4_ROOT ${PS4_ROOT})

    	if( EXISTS "$ENV{SCE_ORBIS_SDK_DIR}" AND IS_DIRECTORY "$ENV{SCE_ORBIS_SDK_DIR}" )
	    	string(REGEX REPLACE "\\\\" "/" PS4_SDK $ENV{SCE_ORBIS_SDK_DIR})
	    	string(REGEX REPLACE "//" "/" PS4_SDK ${PS4_SDK})
	    	get_filename_component(SCE_VERSION "${PS4_SDK}" NAME)
	    endif()
    endif()
    
    # Check if the PS4 SDK can be found
    if( NOT PS4_ROOT OR NOT PS4_SDK )
	    message(FATAL_ERROR "Engine requires PS4 SCE SDK to be installed in order to build for ORBIS.")
    endif()

    set(CMAKE_SYSTEM_NAME Orbis)
    set(PS4 True)

    set(CMAKE_SYSROOT "${PS4_ROOT}")

    # Set compilers to the ones found in PS4 SCE SDK directory
    set(CMAKE_C_COMPILER "${PS4_SDK}/host_tools/bin/orbis-clang.exe")
    set(CMAKE_CXX_COMPILER "${PS4_SDK}/host_tools/bin/orbis-clang++.exe")
    set(CMAKE_ASM_COMPILER "${PS4_SDK}/host_tools/bin/orbis-as.exe")

    # Only search the PS4 SCE SDK, not the remainder of the host file system
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
else ()
	
endif ()


# Include sub-projects.
add_subdirectory ("Tabi")
add_subdirectory("Game")
