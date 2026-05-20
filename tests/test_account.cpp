#include "banking/Account.hpp"
#include <gtest/gtest.h>

using namespace banking;

TEST(AccountTest, ConstructorInitializesNumberAndBalance) {
    Account acc("12345");
    EXPECT_EQ(acc.getNumber(), "12345");
    EXPECT_DOUBLE_EQ(acc.getBalance(), 0.0);
}

TEST(AccountTest, DepositIncreasesBalance) {
    Account acc("12345");
    acc.deposit(100.5);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.5);
}

TEST(AccountTest, DepositThrowsOnNonPositiveAmount) {
    Account acc("12345");
    EXPECT_THROW(acc.deposit(-10), std::invalid_argument);
    EXPECT_THROW(acc.deposit(0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 0.0);
}

TEST(AccountTest, WithdrawDecreasesBalanceWhenSufficientFunds) {
    Account acc("12345");
    acc.deposit(100);
    EXPECT_TRUE(acc.withdraw(30.5));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 69.5);
}

TEST(AccountTest, WithdrawReturnsFalseWhenInsufficientFunds) {
    Account acc("12345");
    acc.deposit(50);
    EXPECT_FALSE(acc.withdraw(100));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 50.0);
}

TEST(AccountTest, WithdrawThrowsOnNonPositiveAmount) {
    Account acc("12345");
    acc.deposit(100);
    EXPECT_THROW(acc.withdraw(-5), std::invalid_argument);
    EXPECT_THROW(acc.withdraw(0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}
