# CMakeList.txt : CMake project for Game
cmake_minimum_required (VERSION 3.8)

# Set sources for Game
set(SOURCES 
	src/main.cpp
)

if(SPACESHOOTER)
    set(HEADERS
		${HEADERS}
	    inc/SpaceShooter/Components/MovementComponent.h
	    inc/SpaceShooter/Components/HealthComponent.h

	    inc/SpaceShooter/Systems/MovementSystem.h

	    inc/SpaceShooter/SpaceShooterGameMode.h
	)

	set(SOURCES
		${SOURCES}
	    src/SpaceShooter/Components/MovementComponent.cpp
	    src/SpaceShooter/Components/HealthComponent.cpp

	    src/SpaceShooter/Systems/MovementSystem.cpp

	    src/SpaceShooter/SpaceShooterGameMode.cpp
	)

	add_compile_definitions(SPACESHOOTER)
else()
	set(HEADERS
		${HEADERS}
		inc/TestGameMode.h
		inc/MovableCamera.h
	)

	set(SOURCES
		${SOURCES}
		src/TestGameMode.cpp
		src/MovableCamera.cpp
	)	
endif()

# Add source to this project's executable.
add_executable (Game ${SOURCES} ${HEADERS})

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

if(SPACESHOOTER)
	target_include_directories(Game PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc/SpaceShooter)
target_link_libraries(Game PRIVATE ECS)
endif()

target_link_libraries(Game PRIVATE Core Logger Input)


add_custom_command(
    TARGET Game
    POST_BUILD
	COMMAND xcopy \"${CMAKE_SOURCE_DIR}/Assets\" \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets\" /S /Y /I /C
)