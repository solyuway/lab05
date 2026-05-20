#!/bin/bash

set -e

echo "=== Building with coverage support ==="

# Clean previous builds
rm -rf build coverage.info coverage_report

mkdir -p build
cd build

# Configure with coverage flags
cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_CXX_FLAGS="--coverage -O0 -g" \
         -DCMAKE_EXE_LINKER_FLAGS="--coverage"

make -j2

echo "=== Running tests ==="
ctest --output-on-failure

# Run tests directly for coverage data
./banking_tests

cd ..

echo "=== Generating coverage report ==="
lcov --capture --directory . --output-file coverage.info --no-external \
     --ignore-errors inconsistent,gcov,source

lcov --remove coverage.info '*/third-party/*' --output-file coverage.info \
     --ignore-errors unused
lcov --remove coverage.info '*/tests/*' --output-file coverage.info \
     --ignore-errors unused
lcov --remove coverage.info '/usr/*' --output-file coverage.info \
     --ignore-errors unused
lcov --remove coverage.info '*/build/*' --output-file coverage.info \
     --ignore-errors unused

echo "=== Coverage summary ==="
lcov --list coverage.info 2>&1 | grep -E "\.(cpp|hpp)" || true

echo "=== Coverage percentages ==="
lcov --summary coverage.info 2>&1 || true

echo "=== Generating HTML report ==="
genhtml coverage.info --output-directory coverage_report --ignore-errors source

echo ""
echo "=========================================="
echo "✅ Coverage report generated in coverage_report/index.html"
echo "=========================================="

# Extract line coverage percentage
if command -v bc &> /dev/null; then
    COVERAGE=$(lcov --summary coverage.info 2>&1 | grep "lines" | awk '{print $2}' | sed 's/%//')
    if [ -n "$COVERAGE" ]; then
        echo "📊 Line Coverage: ${COVERAGE}%"
        if (( $(echo "$COVERAGE == 100" | bc -l) )); then
            echo "🎉 Perfect! 100% code coverage achieved!"
        fi
    fi
fi
