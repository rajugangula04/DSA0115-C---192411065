#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer };

constexpr array<long long, 3> BASE_FARE_PAISE = {
    1000, 2000, 3000
};
constexpr int PEAK_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

long long calculateFare(Zone zone, int hour) {
    int index = static_cast<int>(zone);
    if (index < 0 || index >= 3 || hour < 0 || hour > 23)
        return -1;

    long long fare = BASE_FARE_PAISE[index];
    if (isPeakHour(hour))
        fare += fare * PEAK_PERCENT / 100;
    return fare;
}

class SmartCard {
private:
    long long balancePaise;

public:
    explicit SmartCard(long long initialBalance)
        : balancePaise(initialBalance) {}

    bool pay(long long farePaise) {
        if (farePaise < 0 || balancePaise < farePaise ||
            balancePaise - farePaise < MIN_BALANCE_PAISE)
            return false;
        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const { return balancePaise; }
};

int main() {
    SmartCard card(10000);
    long long fare = calculateFare(Zone::Outer, 18);

    if (fare >= 0 && card.pay(fare)) {
        cout << "Journey allowed\n";
        cout << "Fare Rs " << fare / 100 << '.'
             << setw(2) << setfill('0') << fare % 100 << '\n';
    } else {
        cout << "Journey denied\n";
    }

    cout << "Balance Rs " << card.getBalance() / 100 << '\n';
    return 0;
}
