#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNum, string accHolder, double bal)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << "\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew: " << amount << "\n";
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << fixed << setprecision(2);
        cout << "Account Number: " << accountNumber << "\n"
             << "Account Holder: " << accountHolderName << "\n"
             << "Balance: $" << balance << "\n";
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string accHolder, double bal, double rate)
        : BankAccount(accNum, accHolder, bal), interestRate(rate) {}

    double calculateInterest() const {
        return balance * interestRate / 100;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Interest Rate: " << interestRate << "%\n";
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNum, string accHolder, double bal, double limit)
        : BankAccount(accNum, accHolder, bal), overdraftLimit(limit) {}

    bool checkOverdraft(double amount) const {
        return (balance - amount) >= -overdraftLimit;
    }

    void withdraw(double amount) override {
        if (amount > 0 && checkOverdraft(amount)) {
            balance -= amount;
            cout << "Withdrew: " << amount << "\n";
        } else {
            cout << "Overdraft limit exceeded or invalid amount.\n";
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit: $" << overdraftLimit << "\n";
    }
};

class FixedDepositAccount : public BankAccount {
private:
    int term; 
    double interestRate;

public:
    FixedDepositAccount(string accNum, string accHolder, double bal, int t, double rate)
        : BankAccount(accNum, accHolder, bal), term(t), interestRate(rate) {}

    double calculateInterest() const {
        return balance * (interestRate / 100) * (term / 12.0);
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Term: " << term << " months\n"
             << "Interest Rate: " << interestRate << "%\n";
    }
};

int main() {
    SavingsAccount savings("S001", "John Doe", 5000.0, 2.5);
    CheckingAccount checking("C001", "Jane Doe", 1000.0, 500.0);
    FixedDepositAccount fixed("F001", "Alice Smith", 10000.0, 24, 5.0);

    cout << "Savings Account Info:\n";
    savings.displayAccountInfo();
    cout << "Interest Earned: $" << savings.calculateInterest() << "\n\n";

    cout << "Checking Account Info:\n";
    checking.displayAccountInfo();
    checking.withdraw(1200.0);
    checking.displayAccountInfo();
    cout << "\n";

    cout << "Fixed Deposit Account Info:\n";
    fixed.displayAccountInfo();
    cout << "Interest Earned: $" << fixed.calculateInterest() << "\n";

    return 0;
}

