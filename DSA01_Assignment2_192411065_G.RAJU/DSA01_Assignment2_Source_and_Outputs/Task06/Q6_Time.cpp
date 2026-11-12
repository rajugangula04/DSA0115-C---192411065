#include <iostream>
#include <cstdlib>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend inline int minutesBetween(const Time& a, const Time& b);
    friend inline bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    return abs(first - second);
}

inline bool earlier(const Time& a, const Time& b) {
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';

    Time same1(12, 30), same2(12, 30);
    cout << minutesBetween(same1, same2) << ' '
         << earlier(same1, same2) << '\n';

    Time morning(11, 50), afternoon(12, 10);
    cout << minutesBetween(morning, afternoon) << ' '
         << earlier(morning, afternoon) << '\n';
    return 0;
}
