#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Staff {
protected:
    string name;
    int id;
    double basic;
public:
    Staff(string n, int i, double b) : name(move(n)), id(i), basic(b) {}
    virtual double pay() const = 0;
    virtual void display() const {
        cout << name << " (" << id << ") : " << pay() << '\n';
    }
    virtual ~Staff() = default;
};

class Professor : public Staff {
    double research;
public:
    Professor(string n, int i, double b, double r)
        : Staff(move(n), i, b), research(r) {}
    double pay() const override { return basic + basic * 0.42 + research; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(string n, int i, double b) : Staff(move(n), i, b) {}
    double pay() const override { return basic + basic * 0.42; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(move(n), i, 0), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    vector<unique_ptr<Staff>> employees;
    employees.push_back(make_unique<Professor>("Ravi", 101, 50000, 5000));
    employees.push_back(make_unique<LabAssistant>("Kiran", 102, 25000));
    employees.push_back(make_unique<GuestFaculty>("Meena", 103, 20, 1000));
    for (const auto& employee : employees) employee->display();
}
