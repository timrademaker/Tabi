cmake_minimum_required (VERSION 3.8)

set(ECS_HELPERS_HEADERS
    Helpers/MockSystem.h
    Helpers/TestComponent.h
)

set(ECS_HELPERS_SOURCES
    Helpers/MockSystem.cpp
)

add_library(ECSTestHelpers ${ECS_HELPERS_SOURCES})
target_include_directories(ECSTestHelpers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Helpers)

target_link_libraries(ECSTestHelpers
                      gmock
                      gmock_main
                      ECS
)


set(SOURCES 
    Entity/EntityManagerTests.cpp
    System/SystemManagerTests.cpp
    ECS/ECSTests.cpp
)

set(test_name ecs_tests)
add_executable(${test_name} ${SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} ${GTEST_LDFLAGS})
target_link_libraries(${test_name}
                      gtest 
                      gtest_main 
                      gmock
                      gmock_main
                      ECS
                      ECSTestHelpers
)
    
add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name}.exe)
