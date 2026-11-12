#include <iostream>
using namespace std;

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}
void applyByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void applyByPointer(long long* fee, int percent) {
    *fee -= (*fee) * percent / 100;
}

void change(int a, int& b, int* c) {
    a += 10;
    b += 10;
    *c += 10;
}
int& bigger(int& p, int& q) {
    return p > q ? p : q;
}
void show(int x, int y = 5, int z = 10) {
    cout << x + y + z << ' ';
}

int main() {
    long long fee1 = 45000, fee2 = 45000, fee3 = 45000;
    applyByValue(fee1, 10);
    applyByReference(fee2, 15);
    applyByPointer(&fee3, 25);
    cout << "Call by Value: " << fee1 << '\n';
    cout << "Call by Reference: " << fee2 << '\n';
    cout << "Call by Pointer: " << fee3 << '\n';

    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    cout << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    cout << a << ' ' << c << '\n';
    show(1); show(1, 2); show(1, 2, 3);
    cout << '\n';

    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    cout << "after call by value : " << hostelFee << '\n';
    applyByReference(hostelFee, 10);
    cout << "after call by reference: " << hostelFee << '\n';
    return 0;
}
