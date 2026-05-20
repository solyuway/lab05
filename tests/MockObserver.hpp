#ifndef TESTS_MOCK_OBSERVER_HPP
#define TESTS_MOCK_OBSERVER_HPP

#include "banking/Transaction.hpp"
#include <gmock/gmock.h>

namespace banking {

class MockAccountObserver : public IAccountObserver {
public:
    MOCK_METHOD2(onBalanceChanged, void(const Account& account, double oldBalance));
    
    // Добавим дополнительный метод для трёх параметров, если нужно
    void onBalanceChanged(const Account& account, double oldBalance, double newBalance) override {
        onBalanceChanged(account, oldBalance);
    }
};

} // namespace banking

#endif // TESTS_MOCK_OBSERVER_HPP
