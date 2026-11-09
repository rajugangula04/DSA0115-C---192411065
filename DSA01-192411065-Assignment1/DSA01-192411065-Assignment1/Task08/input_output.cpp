#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int zone, hour;
    long long balancePaise = 10000;

    cout << "Enter zone (1=Inner, 2=Middle, 3=Outer): ";
    if (!(cin >> zone)) {
        cout << "Invalid zone input\n";
        return 1;
    }

    cout << "Enter hour (0-23): ";
    if (!(cin >> hour)) {
        cout << "Invalid hour input\n";
        return 1;
    }

    if (zone < 1 || zone > 3 || hour < 0 || hour > 23) {
        cout << "Input out of range\n";
        return 1;
    }

    long long fare = (zone == 1) ? 1000 :
                     (zone == 2) ? 2000 : 3000;

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak)
        fare += fare * 20 / 100;

    if (balancePaise - fare >= 5000) {
        balancePaise -= fare;
        cout << "Journey Allowed\n";
        cout << "Fare Rs " << fare / 100 << '.'
             << setw(2) << setfill('0') << fare % 100 << '\n';
        cout << "Remaining balance Rs "
             << balancePaise / 100 << '\n';
    } else {
        cout << "Journey Denied\n";
    }

    return 0;
}
