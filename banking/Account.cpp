#include "Account.hpp"
#include <stdexcept>

namespace banking {

Account::Account(const std::string& number)
    : number_(number), balance_(0.0) {}

const std::string& Account::getNumber() const {
    return number_;
}

double Account::getBalance() const {
    return balance_;
}

void Account::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance_ += amount;
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance_) {
        return false;
    }
    balance_ -= amount;
    return true;
}

} // namespace banking
