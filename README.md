# Lab05 - Banking Library with GTest and Mock Objects

## 📊 Code Coverage: 100% ✅

| File | Lines | Functions |
|------|-------|-----------|
| `banking/Account.cpp` | 100% (18/18) | 100% (5/5) |
| `banking/Transaction.cpp` | 100% (23/23) | 100% (3/3) |
| **Total** | **100% (41/41)** | **100% (8/8)** |

## 🧪 Test Results

- **Total tests:** 13
- **Passed:** 13 (100%)
- **Failed:** 0

## 🔧 Build and Test

```bash
# Clone with submodules
git clone --recursive https://github.com/${GITHUB_USERNAME}/lab05
cd lab05

# Build and test
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make && ./banking_tests
