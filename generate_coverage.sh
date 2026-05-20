#!/bin/bash

set -e

echo "=== Building with coverage support ==="
rm -rf build
mkdir -p build
cd build

# Компилируем с флагами coverage
cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_CXX_FLAGS="--coverage" \
         -DCMAKE_EXE_LINKER_FLAGS="--coverage"
make -j2

echo "=== Running tests ==="
ctest --output-on-failure

cd ..

echo "=== Generating coverage report ==="
# Очищаем старые данные покрытия
find . -name "*.gcda" -delete

# Запускаем тесты заново для генерации .gcda файлов
cd build
./banking_tests
cd ..

# Собираем данные о покрытии, игнорируя ошибки
lcov --capture --directory . --output-file coverage.info --no-external \
     --ignore-errors inconsistent,gcov,source \
     --rc lcov_branch_coverage=0

# Удаляем файлы из сторонних библиотек и тестов
lcov --remove coverage.info '*/third-party/*' --output-file coverage.info \
     --ignore-errors unused,unused
lcov --remove coverage.info '*/tests/*' --output-file coverage.info \
     --ignore-errors unused,unused
lcov --remove coverage.info '/usr/*' --output-file coverage.info \
     --ignore-errors unused,unused

echo "=== Coverage summary ==="
lcov --list coverage.info --ignore-errors unused,unused

echo "=== Generating HTML report ==="
genhtml coverage.info --output-directory coverage_report \
       --ignore-errors source,corrupt

echo ""
echo "=========================================="
echo "✅ Coverage report generated in coverage_report/index.html"
echo "=========================================="

# Проверяем процент покрытия
COV_PERCENT=$(lcov --summary coverage.info 2>&1 | grep "lines" | awk '{print $2}' | sed 's/%//')
echo "Coverage: ${COV_PERCENT}%"
