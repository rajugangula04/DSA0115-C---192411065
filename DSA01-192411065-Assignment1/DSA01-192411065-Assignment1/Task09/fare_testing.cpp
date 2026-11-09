#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

constexpr long long MIN_BALANCE_PAISE = 5000;

long long calculateFare(int zone, int hour) {
    if (zone < 1 || zone > 3 || hour < 0 || hour > 23)
        return -1;

    long long fare = (zone == 1) ? 1000 :
                     (zone == 2) ? 2000 : 3000;

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak)
        fare += fare * 20 / 100;

    return fare;
}

void printMoney(long long paise) {
    cout << "Rs " << paise / 100 << '.'
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
}

int main() {
    struct TestCase {
        int zone;
        int hour;
        long long expected;
        string description;
    };

    TestCase tests[] = {
        {1, 11, 1000, "Inner off-peak"},
        {2, 9, 2400, "Middle peak"},
        {3, 12, 3000, "Outer off-peak"},
        {3, 18, 3600, "Outer peak"},
        {1, 8, 1200, "Peak starts at 8 AM"},
        {2, 10, 2000, "10 AM is off-peak"},
        {3, 20, 3000, "8 PM is off-peak"},
        {4, 11, -1, "Invalid zone"}
    };

    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (const auto& test : tests) {
        long long actual = calculateFare(test.zone, test.hour);
        bool ok = (actual == test.expected);
        cout << test.description << ": "
             << (ok ? "PASS" : "FAIL") << " | actual = ";
        if (actual < 0) cout << "Invalid";
        else printMoney(actual);
        cout << '\n';
        if (ok) ++passed;
    }

    cout << "Tests passed: " << passed << "/" << total << '\n';

    long long balance = 6000; // Rs 60
    long long fare = 1000;    // Rs 10
    cout << "Rs 60 balance, Rs 10 fare: "
         << ((balance - fare >= MIN_BALANCE_PAISE)
             ? "Journey allowed" : "Journey denied") << '\n';

    return 0;
}
