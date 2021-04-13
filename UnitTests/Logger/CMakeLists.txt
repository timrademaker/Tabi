cmake_minimum_required (VERSION 3.8)

set(LOGGER_HELPERS_HEADERS
    Helpers/MockSink.h
    Helpers/LogFunctions.h
)

set(LOGGER_HELPERS_SOURCES
    Helpers/MockSink.cpp
    Helpers/LogFunctions.cpp
)

add_library(LoggerTestHelpers ${LOGGER_HELPERS_SOURCES})
target_include_directories(LoggerTestHelpers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Helpers)

target_link_libraries(LoggerTestHelpers
                      gmock
                      gmock_main
                      Logger
)

set(SOURCES 
    Logger/LoggerTests.cpp
    LoggerRegistry/LoggerRegistryTests.cpp
)

set(test_name logger_tests)
add_executable(${test_name} ${SOURCES})
target_compile_options(${test_name} PUBLIC ${GTEST_CFLAGS})
target_link_libraries(${test_name} ${GTEST_LDFLAGS})
target_link_libraries(${test_name}
                      gtest 
                      gtest_main 
                      gmock
                      gmock_main
                      Logger
                      LoggerTestHelpers
)
    
add_test(NAME ${test_name} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name}.exe)
