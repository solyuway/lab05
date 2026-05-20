# Lab05 - Testing with GTest and Mock Objects

## Описание

Библиотека banking с классами `Account` и `Transaction`.  
Модульные тесты с использованием Google Test и Google Mock.  
Покрытие кода: **100%**.

## Требования

- CMake >= 3.10
- C++14 компилятор
- lcov и genhtml (для отчёта о покрытии)

## Сборка и тестирование

```bash
# Сборка с тестами
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make

# Запуск тестов
ctest --output-on-failure
