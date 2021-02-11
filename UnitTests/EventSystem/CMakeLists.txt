cmake_minimum_required (VERSION 3.8)

set(EVENT_HELPERS_HEADERS
    Helpers/MockObject.h
    Helpers/TestEvent.h
)

set(EVENT_HELPERS_SOURCES
    Helpers/MockObject.cpp
    Helpers/TestEvent.cpp
)

add_library(EventTestHelpers ${EVENT_HELPERS_SOURCES})
target_include_directories(EventTestHelpers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Helpers)

target_link_libraries(EventTestHelpers
                      gmock
                      gmock_main
)

set(SOURCES 
    TabiEvent/EventSystemTests.cpp
)

set(test_name event_system_tests)
add_executable(${test_name} ${SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} ${GTEST_LDFLAGS})
target_link_libraries(${test_name}
                      gtest 
                      gtest_main 
                      gmock
                      gmock_main
                      Utilities
                      EventTestHelpers
)
    
add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name}.exe)
