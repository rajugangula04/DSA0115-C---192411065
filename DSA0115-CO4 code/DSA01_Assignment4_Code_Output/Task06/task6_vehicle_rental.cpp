#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string regNo;
    double dailyRate;
    bool rented = false;
public:
    Vehicle(string r, double rate) : regNo(move(r)), dailyRate(rate) {}
    virtual double charge(int days) const = 0;
    bool rent() { if (rented) return false; rented = true; return true; }
    void returnVehicle() { rented = false; }
    bool isRented() const { return rented; }
    string registration() const { return regNo; }
    virtual void display() const {
        cout << regNo << " | Rate: " << dailyRate << " | "
             << (rented ? "Rented" : "Available") << '\n';
    }
    virtual ~Vehicle() = default;
};
class Bicycle : public Vehicle {
public:
    Bicycle(string r, double rate) : Vehicle(move(r), rate) {}
    double charge(int days) const override { return dailyRate * days; }
};
class TwoWheeler : public Vehicle {
    double fuelLevel;
    string serviceDue;
public:
    TwoWheeler(string r, double rate, double fuel, string due)
        : Vehicle(move(r), rate), fuelLevel(fuel), serviceDue(move(due)) {}
    double charge(int days) const override { return dailyRate * days; }
};
class Car : public Vehicle {
    int seats;
    double fuelLevel;
    string serviceDue;
public:
    Car(string r, double rate, int s, double fuel, string due)
        : Vehicle(move(r), rate), seats(s), fuelLevel(fuel), serviceDue(move(due)) {}
    double charge(int days) const override { return dailyRate * days; }
};
class ElectricCar : public Vehicle {
    double batteryKWh, kWhRate;
public:
    ElectricCar(string r, double rate, double battery, double energyRate)
        : Vehicle(move(r), rate), batteryKWh(battery), kWhRate(energyRate) {}
    double charge(int days) const override {
        return dailyRate * days + batteryKWh * kWhRate;
    }
};
class ElectricBus : public Vehicle {
    int seats;
public:
    ElectricBus(string r, double rate, int s) : Vehicle(move(r), rate), seats(s) {}
    double charge(int days) const override { return dailyRate * days; }
};
int main() {
    vector<unique_ptr<Vehicle>> fleet;
    fleet.push_back(make_unique<Bicycle>("B101", 100));
    fleet.push_back(make_unique<TwoWheeler>("T201", 300, 5.0, "2026-12-01"));
    fleet.push_back(make_unique<Car>("C301", 1500, 5, 20.0, "2026-12-10"));
    fleet.push_back(make_unique<ElectricCar>("E401", 2000, 50, 8));
    fleet.push_back(make_unique<ElectricBus>("EB501", 5000, 40));

    cout << "Vehicle Fleet\n";
    for (const auto& v : fleet) v->display();
    cout << "\nRental demonstration\n";
    Vehicle* selected = fleet[0].get();
    if (selected->rent()) {
        cout << selected->registration() << " rented successfully\n";
        int days = 3;
        double lateFee = 50.0; // example assumption
        cout << "Rental charge: " << selected->charge(days) << '\n';
        cout << "Late fee: " << lateFee << '\n';
        cout << "Total: " << selected->charge(days) + lateFee << '\n';
        selected->returnVehicle();
        cout << "Vehicle returned successfully\n";
    }
    cout << "\nFleet after return\n";
    for (const auto& v : fleet) v->display();
    cout << "\nElectric car 2-day charge: " << fleet[3]->charge(2) << '\n';
    cout << "Electric bus 2-day charge: " << fleet[4]->charge(2) << '\n';
}
