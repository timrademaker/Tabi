# CMakeList.txt : CMake project for Game
cmake_minimum_required (VERSION 3.8)

# Set headers for Game
set(HEADERS
	inc/TestGameMode.h
	inc/MovableCamera.h
)

# Set sources for Game
set(SOURCES 
	src/main.cpp
	src/TestGameMode.cpp
	src/MovableCamera.cpp
)

# Add source to this project's executable.
add_executable (Game ${SOURCES} ${HEADERS})

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

target_link_libraries(Game PRIVATE Core Logger Input)
target_link_libraries(Game PRIVATE ResourceManager imgui)


add_custom_command(
    TARGET Game
    POST_BUILD
	COMMAND xcopy \"${CMAKE_SOURCE_DIR}/Assets\" \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets\" /S /Y /I /C
)