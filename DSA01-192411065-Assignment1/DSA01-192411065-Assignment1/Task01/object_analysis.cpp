#include <iostream>
#include <string>
using namespace std;

enum class PassengerType { Regular, Student, SeniorCitizen };
enum class Zone { Inner, Middle, Outer };

class Passenger {
private:
    int passengerId;
    string name;
    PassengerType type;

public:
    Passenger(int id, string passengerName, PassengerType passengerType)
        : passengerId(id), name(passengerName), type(passengerType) {}

    void display() const {
        cout << "Passenger ID: " << passengerId << '\n';
        cout << "Name: " << name << '\n';
    }

    PassengerType getType() const { return type; }
};

class SmartCard {
private:
    long long balancePaise;

public:
    explicit SmartCard(long long initialBalancePaise)
        : balancePaise(initialBalancePaise) {}

    long long getBalance() const { return balancePaise; }

    bool deductFare(long long farePaise) {
        constexpr long long MIN_BALANCE = 5000;
        if (farePaise < 0 || balancePaise - farePaise < MIN_BALANCE)
            return false;
        balancePaise -= farePaise;
        return true;
    }
};

int main() {
    Passenger passenger(101, "Raju", PassengerType::Student);
    SmartCard card(10000);

    passenger.display();
    cout << "Initial balance: Rs " << card.getBalance() / 100 << '\n';

    if (card.deductFare(2000))
        cout << "Journey allowed\n";
    else
        cout << "Journey denied\n";

    cout << "Final balance: Rs " << card.getBalance() / 100 << '\n';
    return 0;
}
