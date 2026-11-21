#include <iostream>
using namespace std;
class Cart {
    double amount;
public:
    explicit Cart(double a) : amount(a) {}
    double total() const { return amount; }
};
int main() {
    Cart a(250), b(500), c(350);
    Cart* carts[] = {&a, &b, &c};
    int best = 0;
    for (int i = 1; i < 3; ++i)
        if (carts[i]->total() > carts[best]->total()) best = i;
    cout << "Highest cart total: " << carts[best]->total() << '\n';
}
