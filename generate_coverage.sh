#!/bin/bash

set -e

echo "=== Building with coverage support ==="

# Clean
rm -rf build coverage.info coverage_report

# Configure
mkdir -p build
cd build
cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_CXX_FLAGS="--coverage -O0 -g" \
         -DCMAKE_EXE_LINKER_FLAGS="--coverage"

# Build
make -j2

# Run tests
echo "=== Running tests ==="
./banking_tests

cd ..

# Generate coverage from build directory
echo "=== Generating coverage report ==="
lcov --capture --directory build --output-file coverage.info --no-external \
     --ignore-errors inconsistent,gcov,source,empty

# Remove unwanted files
lcov --remove coverage.info '*/third-party/*' --output-file coverage.info \
     --ignore-errors unused,empty
lcov --remove coverage.info '*/tests/*' --output-file coverage.info \
     --ignore-errors unused,empty
lcov --remove coverage.info '/usr/*' --output-file coverage.info \
     --ignore-errors unused,empty

# Show coverage
echo ""
echo "=== Coverage Summary ==="
lcov --summary coverage.info 2>&1 || true

echo ""
echo "=== File Details ==="
lcov --list coverage.info 2>&1 | grep -E "(Account|Transaction)\.cpp" -A1

# Generate HTML
genhtml coverage.info --output-directory coverage_report --ignore-errors source

echo ""
echo "=========================================="
echo "✅ Coverage report: coverage_report/index.html"
echo "=========================================="

# Verify 100%
if lcov --list coverage.info 2>&1 | grep -q "Account.cpp.*100%.*100%"; then
    echo "✅ Account.cpp: 100% coverage"
else
    echo "⚠️ Account.cpp coverage may not be 100%"
fi

if lcov --list coverage.info 2>&1 | grep -q "Transaction.cpp.*100%.*100%"; then
    echo "✅ Transaction.cpp: 100% coverage"
else
    echo "⚠️ Transaction.cpp coverage may not be 100%"
fi
