#include <iostream>
#include <iomanip>
using namespace std;

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };

constexpr long long MIN_BALANCE_PAISE = 5000;

long long calculateFare(Zone zone, bool peak) {
    long long fare = 0;

    switch (zone) {
        case Zone::Inner:  fare = 1000; break;
        case Zone::Middle: fare = 2000; break;
        case Zone::Outer:  fare = 3000; break;
        default: return -1;
    }

    if (peak)
        fare += fare * 20 / 100;

    return fare;
}

bool canTravel(long long balance, long long fare) {
    return fare >= 0 && balance >= fare &&
           balance - fare >= MIN_BALANCE_PAISE;
}

int main() {
    long long balance = 10000;

    struct Trip { Zone zone; bool peak; };
    Trip trips[] = {
        {Zone::Inner, false},
        {Zone::Outer, true},
        {Zone::Middle, false}
    };

    for (const Trip& trip : trips) {
        long long fare = calculateFare(trip.zone, trip.peak);

        if (canTravel(balance, fare)) {
            balance -= fare;
            cout << "Fare Rs " << fare / 100 << '.'
                 << setw(2) << setfill('0') << fare % 100
                 << setfill(' ') << " balance Rs "
                 << balance / 100 << '\n';
        } else {
            cout << "Denied (low balance) balance Rs "
                 << balance / 100 << '\n';
        }
    }
    return 0;
}
