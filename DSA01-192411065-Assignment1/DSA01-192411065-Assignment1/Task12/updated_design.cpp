#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };

constexpr array<long long, 4> FARE_PAISE = {
    1000, 2000, 3000, 6000
};
constexpr int PEAK_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr long long MIN_BALANCE_PAISE = 5000;

class MonthlyPass {
private:
    bool active = false;
    bool allowedZones[4] = {false, false, false, false};

public:
    void activate(Zone first, Zone second) {
        allowedZones[static_cast<int>(first)] = true;
        allowedZones[static_cast<int>(second)] = true;
        active = true;
    }

    bool covers(Zone zone) const {
        int index = static_cast<int>(zone);
        return active && index >= 0 && index < 4 &&
               allowedZones[index];
    }
};

class SmartCard {
private:
    long long balancePaise;

public:
    explicit SmartCard(long long initialBalance)
        : balancePaise(initialBalance) {}

    bool deduct(long long farePaise) {
        if (farePaise < 0 || balancePaise < farePaise ||
            balancePaise - farePaise < MIN_BALANCE_PAISE)
            return false;
        balancePaise -= farePaise;
        return true;
    }

    long long balance() const { return balancePaise; }
};

long long calculateFare(Zone zone, int hour, bool weekend,
                        const MonthlyPass& pass) {
    int index = static_cast<int>(zone);
    if (index < 0 || index >= 4 || hour < 0 || hour > 23)
        return -1;

    if (pass.covers(zone))
        return 0;

    long long fare = FARE_PAISE[index];

    // Assumption: weekend discount replaces, rather than combines
    // with, the peak-hour surcharge.
    if (weekend)
        fare -= fare * WEEKEND_DISCOUNT_PERCENT / 100;
    else if ((hour >= 8 && hour < 10) ||
             (hour >= 17 && hour < 20))
        fare += fare * PEAK_PERCENT / 100;

    return fare;
}

void printMoney(long long paise) {
    cout << "Rs " << paise / 100 << '.'
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
}

int main() {
    SmartCard card(20000); // Rs 200
    MonthlyPass pass;
    pass.activate(Zone::Inner, Zone::Middle);

    struct Trip {
        Zone zone;
        int hour;
        bool weekend;
    };

    Trip trips[] = {
        {Zone::Inner, 11, false},
        {Zone::Outer, 18, false},
        {Zone::Airport, 12, true},
        {Zone::Middle, 13, false}
    };

    for (const auto& trip : trips) {
        long long fare = calculateFare(
            trip.zone, trip.hour, trip.weekend, pass
        );

        if (fare < 0) {
            cout << "Invalid zone or time\n";
        } else if (card.deduct(fare)) {
            cout << "Fare ";
            printMoney(fare);
            cout << '\n';
        } else {
            cout << "Journey denied: minimum balance rule\n";
        }

        cout << "Balance ";
        printMoney(card.balance());
        cout << '\n';
    }

    return 0;
}
