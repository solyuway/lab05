cmake_minimum_required(VERSION 3.14)
project(banking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

option(BUILD_TESTS "Build tests" OFF)

add_library(banking STATIC
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTS)
    enable_testing()
    
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.0
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    # Отключаем -Werror для Google Test
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(gtest PRIVATE -Wno-error -Wno-unused-variable -Wno-unused-but-set-variable)
        target_compile_options(gtest_main PRIVATE -Wno-error)
        target_compile_options(gmock PRIVATE -Wno-error)
        target_compile_options(gmock_main PRIVATE -Wno-error)
    endif()
    
    file(GLOB TEST_SOURCES tests/*.cpp)
    add_executable(banking_tests ${TEST_SOURCES})
    
    target_include_directories(banking_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    target_link_libraries(banking_tests
        banking
        gtest_main
        gmock
        pthread
    )
    
    target_compile_options(banking_tests PRIVATE --coverage -O0 -g)
    target_link_options(banking_tests PRIVATE --coverage)
    
    add_test(NAME BankingTests COMMAND banking_tests)
endif()
