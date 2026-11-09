#include <iostream>
#include <climits>
#include <string>
using namespace std;

int main() {
    int passengerId = 101;
    long long balancePaise = 100000;
    double exampleMeasurement = 10.5;
    bool peakHour = true;
    char category = 'S';
    string passengerName = "Raju";

    cout << "Passenger ID: " << passengerId << '\n';
    cout << "Passenger name: " << passengerName << '\n';
    cout << "Balance: " << balancePaise << " paise\n";
    cout << "Example double: " << exampleMeasurement << '\n';
    cout << "Peak hour: " << boolalpha << peakHour << '\n';
    cout << "Category: " << category << '\n';

    cout << "\nTypical type sizes on this compiler:\n";
    cout << "char: " << sizeof(char) << '\n';
    cout << "bool: " << sizeof(bool) << '\n';
    cout << "int: " << sizeof(int) << '\n';
    cout << "double: " << sizeof(double) << '\n';
    cout << "long long: " << sizeof(long long) << '\n';

    cout << "\nINT_MAX: " << INT_MAX << '\n';
    cout << "LLONG_MAX: " << LLONG_MAX << '\n';
    return 0;
}
