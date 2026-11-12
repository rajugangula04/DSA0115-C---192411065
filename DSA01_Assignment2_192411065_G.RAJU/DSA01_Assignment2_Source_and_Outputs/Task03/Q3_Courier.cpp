#include <iostream>
using namespace std;

struct Parcel {
    double weight;
    bool express;
    bool insured;
};

void charge(int grams) {
    cout << "Integer grams: " << grams << " g\n";
}
void charge(double kg, bool express = false, bool insured = false) {
    double cost = kg * 50;
    if (express) cost += 30;
    if (insured) cost += 20;
    cout << "Weight in kg: " << cost << '\n';
}
void charge(const Parcel& p) {
    double cost = p.weight * 50;
    if (p.express) cost += 30;
    if (p.insured) cost += 20;
    cout << "Parcel charge: " << cost << '\n';
}

int main() {
    Parcel p{3.0, true, true};
    charge(2);
    charge(2.0f);
    charge(2.5);
    charge(2.5, true);
    charge(2.5, true, true);
    charge(p);
    return 0;
}
