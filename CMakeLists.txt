cmake_minimum_required(VERSION 3.10)
project(banking VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги для coverage (без -Werror)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic --coverage")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")

# Опции сборки
option(BUILD_TESTS "Build tests" OFF)

# Библиотека banking
add_library(banking STATIC
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Установка библиотеки
install(TARGETS banking DESTINATION lib)
install(FILES 
    banking/Account.hpp 
    banking/Transaction.hpp 
    DESTINATION include/banking
)

# Если тесты включены
if(BUILD_TESTS)
    enable_testing()
    
    # Добавляем Google Test с подавлением предупреждений
    add_subdirectory(third-party/gtest)
    
    # Подавляем предупреждения для gtest (решение проблемы с -Werror)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(gtest PRIVATE -Wno-maybe-uninitialized)
        target_compile_options(gtest_main PRIVATE -Wno-maybe-uninitialized)
        target_compile_options(gmock PRIVATE -Wno-maybe-uninitialized)
        target_compile_options(gmock_main PRIVATE -Wno-maybe-uninitialized)
    endif()
    
    # Добавляем тесты
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
    )
    
    # Включаем coverage флаги для тестов
    target_compile_options(banking_tests PRIVATE --coverage)
    target_link_options(banking_tests PRIVATE --coverage)
    
    add_test(NAME BankingTests COMMAND banking_tests)
endif()
