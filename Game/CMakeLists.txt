# CMakeList.txt : CMake project for Game
cmake_minimum_required (VERSION 3.8)

# Set headers for Game
set(HEADERS
	inc/TestGameMode.h
)

# Set sources for Game
set(SOURCES 
	src/main.cpp
	src/TestGameMode.cpp
)

# Add source to this project's executable.
add_executable (Game ${SOURCES} ${HEADERS})

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(Game PRIVATE Core Logger)
