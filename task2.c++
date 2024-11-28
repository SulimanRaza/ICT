#include <iostream>
#include <string>
#include <sstream>  
using namespace std;

class Account {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;
    string transactionHistory[10];
    int transactionCount;

public:
    Account(string accountNumber, string accountHolderName, double initialBalance)
        : accountNumber(accountNumber), accountHolderName(accountHolderName), balance(initialBalance), transactionCount(0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory[transactionCount++] = "Deposited: $" + convertToString(amount);
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            transactionHistory[transactionCount++] = "Withdrawn: $" + convertToString(amount);
        } else {
            cout << "Insufficient funds or invalid withdrawal amount!" << endl;
        }
    }

    void displayDetails() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }

    void displayTransactionHistory() {
        cout << "\nTransaction History for Account " << accountNumber << ":\n";
        for (int i = 0; i < transactionCount; i++) {
            cout << transactionHistory[i] << endl;
        }
    }

protected:  // Change from private to protected so derived classes can access
    string convertToString(double number) {
        stringstream ss;
        ss << number;
        return ss.str();
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accountNumber, string accountHolderName, double initialBalance, double interestRate)
        : Account(accountNumber, accountHolderName, initialBalance), interestRate(interestRate) {}

    double calculateInterest() {
        return balance * (interestRate / 100);
    }

    void displayDetails() {
        Account::displayDetails();
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Interest Earned: $" << calculateInterest() << endl;
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(string accountNumber, string accountHolderName, double initialBalance, double overdraftLimit)
        : Account(accountNumber, accountHolderName, initialBalance), overdraftLimit(overdraftLimit) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            transactionHistory[transactionCount++] = "Withdrawn: $" + convertToString(amount) + " (Overdraft allowed)";
        } else {
            cout << "Withdrawal amount exceeds overdraft limit!" << endl;
        }
    }

    void displayDetails() {
        Account::displayDetails();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
    }
};

int main() {
    SavingsAccount savingsAccount("XYZ123", "Suliman", 1000.0, 5.0);
    CurrentAccount currentAccount("ABC123", "Hassan", 500.0, 200.0);

    savingsAccount.deposit(200.0);
    savingsAccount.withdraw(150.0);

    currentAccount.deposit(1000.0);
    currentAccount.withdraw(600.0);
    currentAccount.withdraw(700.0);

    cout << "\nSavings Account Details and Transaction History:\n";
    savingsAccount.displayDetails();
    savingsAccount.displayTransactionHistory();

    cout << "\nCurrent Account Details and Transaction History:\n";
    currentAccount.displayDetails();
    currentAccount.displayTransactionHistory();

    return 0;
}