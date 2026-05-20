#ifndef TESTS_MOCK_ACCOUNT_HPP
#define TESTS_MOCK_ACCOUNT_HPP

#include "banking/Account.hpp"
#include <gmock/gmock.h>

namespace banking {

class MockAccount : public Account {
public:
    MockAccount(const std::string& number) : Account(number) {}
    
    MOCK_METHOD1(deposit, void(double amount));
    MOCK_METHOD1(withdraw, bool(double amount));
};

} // namespace banking

#endif // TESTS_MOCK_ACCOUNT_HPP
