#include "Transaction.hpp"
#include <stdexcept>

namespace banking {

Transaction::Transaction(std::shared_ptr<Account> from, std::shared_ptr<Account> to)
    : from_(from), to_(to), observer_(nullptr) {}

void Transaction::setObserver(std::shared_ptr<IAccountObserver> observer) {
    observer_ = observer;
}

bool Transaction::execute(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Transaction amount must be positive");
    }
    if (!from_ || !to_) {
        throw std::logic_error("Invalid accounts in transaction");
    }

    double oldFromBalance = from_->getBalance();
    double oldToBalance = to_->getBalance();

    if (!from_->withdraw(amount)) {
        return false;
    }

    try {
        to_->deposit(amount);
        
        if (observer_) {
            observer_->onBalanceChanged(*from_, oldFromBalance, from_->getBalance());
            observer_->onBalanceChanged(*to_, oldToBalance, to_->getBalance());
        }
        return true;
    } catch (...) {
        // Rollback: вернуть средства на счёт from
        from_->deposit(amount);
        throw;
    }
}

} // namespace banking
