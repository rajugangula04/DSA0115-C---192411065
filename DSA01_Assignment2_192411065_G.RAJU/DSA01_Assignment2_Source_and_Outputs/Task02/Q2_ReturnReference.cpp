#include <iostream>
using namespace std;

int& highestMark(int marks[], int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[maxIndex]) maxIndex = i;
    return marks[maxIndex];
}

// Deliberately unsafe demonstration: never call or use this returned reference.
int& dangerousFunction() {
    int local = 50;
    return local; // returning reference to a local variable: undefined behaviour
}

int main() {
    int marks[5] = {75, 85, 92, 80, 88};
    cout << "Highest mark: " << highestMark(marks, 5) << '\n';
    highestMark(marks, 5) += 2;
    cout << "After moderation: " << highestMark(marks, 5) << '\n';
    highestMark(marks, 5) = 100;
    cout << "After updating: " << highestMark(marks, 5) << '\n';
    return 0;
}
