# Lab05 - Banking Library with 100% Test Coverage

[![CI with Coverage](https://github.com/${GITHUB_USERNAME}/lab05/actions/workflows/ci.yml/badge.svg)](https://github.com/${GITHUB_USERNAME}/lab05/actions/workflows/ci.yml)
[![Coverage Status](https://img.shields.io/badge/coverage-100%25-brightgreen)](https://${GITHUB_USERNAME}.github.io/lab05/coverage/)

## 📊 Coverage Report

[![Coverage Report](https://img.shields.io/badge/📊-View%20Coverage%20Report-blue)](https://${GITHUB_USERNAME}.github.io/lab05/coverage/)

**Current coverage: 100%** ✅

| File | Lines | Functions |
|------|-------|-----------|
| Account.cpp | 100% (18/18) | 100% (5/5) |
| Transaction.cpp | 100% (23/23) | 100% (3/3) |

## Описание

Библиотека banking с классами `Account` и `Transaction`.  
Модульные тесты с использованием Google Test и Google Mock.  
**Покрытие кода: 100%**

## 📋 Требования

- CMake >= 3.10
- C++14 компилятор
- lcov и genhtml (для отчёта о покрытии)

## 🔧 Сборка и тестирование

```bash
# Клонирование с submodules
git clone --recursive https://github.com/${GITHUB_USERNAME}/lab05
cd lab05

# Сборка с тестами
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make

# Запуск тестов
ctest --output-on-failure
