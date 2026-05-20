#include "banking/Transaction.hpp"
#include "MockObserver.hpp"
#include "MockAccount.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace banking;
using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {
        from = std::make_shared<Account>("FROM123");
        to = std::make_shared<Account>("TO456");
        from->deposit(200);
    }

    std::shared_ptr<Account> from;
    std::shared_ptr<Account> to;
};

TEST_F(TransactionTest, ExecuteSuccessfulTransfer) {
    Transaction transaction(from, to);
    EXPECT_TRUE(transaction.execute(50.0));
    
    EXPECT_DOUBLE_EQ(from->getBalance(), 150.0);
    EXPECT_DOUBLE_EQ(to->getBalance(), 50.0);
}

TEST_F(TransactionTest, ExecuteFailsWhenInsufficientFunds) {
    Transaction transaction(from, to);
    EXPECT_FALSE(transaction.execute(300.0));
    
    EXPECT_DOUBLE_EQ(from->getBalance(), 200.0);
    EXPECT_DOUBLE_EQ(to->getBalance(), 0.0);
}

TEST_F(TransactionTest, ExecuteThrowsOnNonPositiveAmount) {
    Transaction transaction(from, to);
    EXPECT_THROW(transaction.execute(-10), std::invalid_argument);
    EXPECT_THROW(transaction.execute(0), std::invalid_argument);
}

TEST_F(TransactionTest, ExecuteThrowsWhenAccountsAreInvalid) {
    Transaction invalidFrom(nullptr, to);
    EXPECT_THROW(invalidFrom.execute(50), std::logic_error);
    
    Transaction invalidTo(from, nullptr);
    EXPECT_THROW(invalidTo.execute(50), std::logic_error);
}

TEST_F(TransactionTest, ObserverIsNotifiedOnSuccessfulTransfer) {
    auto mockObserver = std::make_shared<MockAccountObserver>();
    
    EXPECT_CALL(*mockObserver, onBalanceChanged(_, 200.0)).Times(1);
    EXPECT_CALL(*mockObserver, onBalanceChanged(_, 0.0)).Times(1);
    
    Transaction transaction(from, to);
    transaction.setObserver(mockObserver);
    transaction.execute(50.0);
}

TEST(TransactionTestWithMocks, RollbackOnDepositFailure) {
    auto mockFrom = std::make_shared<MockAccount>("FROM");
    auto mockTo = std::make_shared<MockAccount>("TO");
    
    // Настройка поведения mock-объектов
    EXPECT_CALL(*mockFrom, withdraw(50.0)).WillOnce(Return(true));
    EXPECT_CALL(*mockTo, deposit(50.0)).WillOnce(Throw(std::runtime_error("Deposit failed")));
    EXPECT_CALL(*mockFrom, deposit(50.0)).Times(1);  // Ожидаем rollback
    
    Transaction transaction(mockFrom, mockTo);
    EXPECT_THROW(transaction.execute(50.0), std::runtime_error);
}

TEST(TransactionTestWithMocks, WithdrawFailsNoDepositAttempt) {
    auto mockFrom = std::make_shared<MockAccount>("FROM");
    auto mockTo = std::make_shared<MockAccount>("TO");
    
    EXPECT_CALL(*mockFrom, withdraw(50.0)).WillOnce(Return(false));
    EXPECT_CALL(*mockTo, deposit(_)).Times(0);  // Не должно вызываться
    
    Transaction transaction(mockFrom, mockTo);
    EXPECT_FALSE(transaction.execute(50.0));
}
