# CMakeList.txt : CMake project for Game
cmake_minimum_required (VERSION 3.8)

# Set headers for Game
set(HEADERS)

# Set sources for Game
set(SOURCES src/main.cpp)

# Add source to this project's executable.
add_executable (Game ${SOURCES} ${HEADERS})

target_link_libraries(Game PRIVATE Core Logger)
