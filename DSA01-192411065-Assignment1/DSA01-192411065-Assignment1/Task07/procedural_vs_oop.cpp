#include <iostream>
using namespace std;

// Procedural example
bool canTravelProcedural(long long balance, long long fare) {
    return fare >= 0 && balance - fare >= 5000;
}

class SmartCard {
private:
    long long balancePaise;

public:
    explicit SmartCard(long long initialBalance)
        : balancePaise(initialBalance) {}

    bool deduct(long long fare) {
        if (fare < 0 || balancePaise - fare < 5000)
            return false;
        balancePaise -= fare;
        return true;
    }

    long long getBalance() const { return balancePaise; }
};

int main() {
    long long proceduralBalance = 10000;
    long long fare = 2000;

    if (canTravelProcedural(proceduralBalance, fare)) {
        proceduralBalance -= fare;
        cout << "Procedural: Journey allowed, balance Rs "
             << proceduralBalance / 100 << '\n';
    }

    SmartCard card(10000);
    if (card.deduct(fare))
        cout << "OOP: Journey allowed, balance Rs "
             << card.getBalance() / 100 << '\n';

    return 0;
}
