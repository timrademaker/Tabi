cmake_minimum_required (VERSION 3.8)

set(COLLISION_HELPERS_HEADERS
    Helpers/MockCollisionCallbackObject.h
    Helpers/CollisionMatchers.h
)

set(COLLISION_HELPERS_SOURCES
    Helpers/MockCollisionCallbackObject.cpp
    Helpers/CollisionMatchers.cpp
)

add_library(CollisionTestHelpers ${COLLISION_HELPERS_SOURCES})
target_include_directories(CollisionTestHelpers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Helpers)

target_link_libraries(CollisionTestHelpers
                      gmock
                      gmock_main
                      Collision
)

set(SOURCES 
    GJK/GJKTests.cpp
    ECS/CollisionSystemTests.cpp
)

set(test_name collision_tests)
add_executable(${test_name} ${SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} ${GTEST_LDFLAGS})
target_link_libraries(${test_name}
                      gtest 
                      gtest_main 
                      gmock
                      gmock_main
                      Collision
                      CollisionTestHelpers
)
    
add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name}.exe)
