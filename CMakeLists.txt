cmake_minimum_required(VERSION 3.10)
project(banking VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_COVERAGE "Enable coverage" OFF)

add_library(banking STATIC
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(ENABLE_COVERAGE)
    target_compile_options(banking PRIVATE --coverage -O0 -g)
    target_link_options(banking PRIVATE --coverage)
endif()

install(TARGETS banking DESTINATION lib)
install(FILES 
    banking/Account.hpp 
    banking/Transaction.hpp 
    DESTINATION include/banking
)

if(BUILD_TESTS)
    enable_testing()
    
    add_subdirectory(third-party/gtest)
    
    file(GLOB TEST_SOURCES tests/*.cpp)
    add_executable(banking_tests ${TEST_SOURCES})
    
    target_include_directories(banking_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest/googlemock/include
    )
    
    target_link_libraries(banking_tests
        banking
        gtest_main
        gmock
        pthread
    )
    
    if(ENABLE_COVERAGE)
        target_compile_options(banking_tests PRIVATE --coverage -O0 -g)
        target_link_options(banking_tests PRIVATE --coverage)
    endif()
    
    add_test(NAME BankingTests COMMAND banking_tests)
endif()
