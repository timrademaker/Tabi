cmake_minimum_required (VERSION 3.8)

set(SOURCES 
    mat4/Scaling.cpp
    mat4/Translation.cpp
    mat4/Rotation.cpp
    mat4/Operators.cpp
    mat4/Misc.cpp
)

set(test_name math_tests)
add_executable(${test_name} ${SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} ${GTEST_LDFLAGS})
target_link_libraries(${test_name}
                      gtest 
                      gtest_main 
                      Math
)
    
# target_link_libraries(${test_name} Tabi Tabi_Test)
    
add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name}.exe)