#ifndef BANKING_ACCOUNT_HPP
#define BANKING_ACCOUNT_HPP

#include <string>
#include <ostream>

namespace banking {

class Account {
public:
    explicit Account(const std::string& number);
    virtual ~Account() = default;  // virtual для возможности мокирования

    const std::string& getNumber() const;
    double getBalance() const;
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

private:
    std::string number_;
    double balance_;
};

} // namespace banking

#endif // BANKING_ACCOUNT_HPP
