# CMakeLists.txt: CMake project for Logger
cmake_minimum_required (VERSION 3.8)

# Set headers for Logger
set(HEADERS
    inc/ConsoleSink.h
    inc/ISink.h
    inc/LoggerRegistry.h
    inc/Logging.h
    inc/TabiLogger.h
)

# Set sources for Logger
set(SOURCES
    src/ConsoleSink.cpp
    src/LoggerRegistry.cpp
    src/Logging.cpp
    src/TabiLogger.cpp
)

# Add source to this project's executable.
# Don't specify STATIC or SHARED explicitly, as the type of library is determined through the variable BUILD_SHARED_LIBS
add_library(Logger EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Logger PUBLIC TabiCommon spdlog)
