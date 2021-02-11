cmake_minimum_required (VERSION 3.8)


set(RESOURCE_MANAGER_HELPERS_HEADERS
    Helpers/TestResource.h
)

set(RESOURCE_MANAGER_HELPERS_SOURCES
    Helpers/TestResource.cpp
)

add_library(ResourceManagerHelpers ${RESOURCE_MANAGER_HELPERS_SOURCES})
target_include_directories(ResourceManagerHelpers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Helpers)

target_link_libraries(ResourceManagerHelpers
                      ResourceManager
)


set(SOURCES 
    ResourceManager/ResourceManagerTests.cpp
)

set(test_name resource_manager_tests)
add_executable(${test_name} ${SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} ${GTEST_LDFLAGS})
target_link_libraries(${test_name}
                      gtest 
                      gtest_main 
                      ResourceManager
                      ResourceManagerHelpers
)
    
add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name}.exe)
