#include <iostream>
using namespace std;

class SavingsAccount {
private:
    int accountNumber;
    double balance;
    double transactions[10];
    int count;

    void addTransaction(double amount) {
        if (count == 10) {
            for (int i = 0; i < 9; ++i)
                transactions[i] = transactions[i + 1];
            count = 9;
        }
        transactions[count++] = amount;
    }

public:
    SavingsAccount(int number, double initialBalance)
        : accountNumber(number), balance(initialBalance), count(0) {}

    void deposit(double amount);
    void withdraw(double amount);
    void miniStatement() const;
};

void SavingsAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        addTransaction(amount);
        cout << "Deposit successful\n";
    } else cout << "Invalid deposit\n";
}

void SavingsAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        addTransaction(-amount);
        cout << "Withdrawal successful\n";
    } else cout << "Insufficient balance or invalid amount\n";
}

void SavingsAccount::miniStatement() const {
    cout << "\nAccount Number: " << accountNumber << '\n';
    cout << "Balance: " << balance << '\n';
    cout << "Last Transactions:\n";
    for (int i = 0; i < count; ++i) cout << transactions[i] << '\n';
}

int main() {
    SavingsAccount account(1001, 5000);
    account.deposit(1000);
    account.withdraw(500);
    account.deposit(2000);
    account.withdraw(300);
    account.miniStatement();
    return 0;
}
