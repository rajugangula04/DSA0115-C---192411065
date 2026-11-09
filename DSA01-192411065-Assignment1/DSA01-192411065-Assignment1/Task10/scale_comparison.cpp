#include <iostream>
#include <climits>
using namespace std;

int main() {
    const long long journeys = 3000000;
    const long long farePaise = 3000; // Rs 30

    long long totalPaise = journeys * farePaise;
    long long totalRupees = totalPaise / 100;

    cout << "Total journeys: " << journeys << '\n';
    cout << "Total collection in paise: " << totalPaise << '\n';
    cout << "Total collection in rupees: " << totalRupees << '\n';
    cout << "INT_MAX: " << INT_MAX << '\n';

    if (totalPaise > INT_MAX)
        cout << "32-bit int cannot store total paise\n";
    else
        cout << "32-bit int can store total paise\n";

    cout << "long long is used for accumulated paise.\n";
    return 0;
}
