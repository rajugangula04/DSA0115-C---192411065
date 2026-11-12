#include <iostream>
using namespace std;

class SavingsAccount {
    static const int SIZE = 50;
    int accountNumber;
    double balance;
    double transactions[SIZE];
    int start;
    int count;

public:
    SavingsAccount(int number, double initialBalance)
        : accountNumber(number), balance(initialBalance),
          start(0), count(0) {}

    void addTransaction(double amount) {
        if (count < SIZE) {
            int position = (start + count) % SIZE;
            transactions[position] = amount;
            ++count;
        } else {
            transactions[start] = amount;
            start = (start + 1) % SIZE;
        }
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            addTransaction(amount);
        }
    }

    void miniStatement() const {
        cout << "Account Number: " << accountNumber << '\n';
        cout << "Balance: " << balance << '\n';
        cout << "Last Transactions (" << count << "):\n";
        for (int i = 0; i < count; ++i) {
            int position = (start + i) % SIZE;
            cout << transactions[position] << '\n';
        }
    }
};

int main() {
    SavingsAccount account(1001, 50000);
    for (int i = 1; i <= 55; ++i) account.deposit(100);
    account.miniStatement();
    return 0;
}
