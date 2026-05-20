#ifndef BANKING_TRANSACTION_HPP
#define BANKING_TRANSACTION_HPP

#include "Account.hpp"
#include <memory>

namespace banking {

class IAccountObserver {
public:
    virtual ~IAccountObserver() = default;
    virtual void onBalanceChanged(const Account& account, double oldBalance, double newBalance) = 0;
};

class Transaction {
public:
    Transaction(std::shared_ptr<Account> from, std::shared_ptr<Account> to);
    ~Transaction() = default;

    bool execute(double amount);
    void setObserver(std::shared_ptr<IAccountObserver> observer);

private:
    std::shared_ptr<Account> from_;
    std::shared_ptr<Account> to_;
    std::shared_ptr<IAccountObserver> observer_;
};

} // namespace banking

#endif // BANKING_TRANSACTION_HPP
