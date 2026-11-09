#include <iostream>
using namespace std;

int main() {
    int a = 7, b = 2;
    double implicitResult = a / b;
    double explicitResult = static_cast<double>(a) / b;

    cout << implicitResult << ' ' << explicitResult << '\n';

    char ch = 'A' + 2;
    cout << ch << ' ' << ch + 1 << '\n';

    bool flag = 5;
    cout << flag << ' ' << boolalpha << flag << '\n';

    unsigned int u = 1;
    int s = -1;
    cout << (s < u ? "s < u" : "s >= u") << '\n';
    return 0;
}
