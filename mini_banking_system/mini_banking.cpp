#include <iostream>
#include <string>
using namespace std;

struct Account {
    string name;
    int id;
    double balance;
};

Account user;

void createAccount() {
    cout << "Create account\n";
    cout << "Enter your name: ";
    getline(cin >> ws, user.name);
    cout << "Enter account ID (numbers only): ";
    while (!(cin >> user.id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a valid number for account ID: ";
    }
    user.balance = 0.0;
    cin.ignore();
    cout << "Account created successfully!\n\n";
}

void deposit() {
    double amount;
    cout << "Enter amount to deposit: R";
    cin >> amount;
    if (amount > 0) {
        user.balance += amount;
        cout << "Deposit successful. New balance: R" << user.balance << "\n\n";
    } else {
        cout << "Invalid amount.\n\n";
    }
    cin.ignore();
}

void withdraw() {
    double amount;
    cout << "Enter amount to withdraw: R";
    cin >> amount;
    if (amount > 0 && amount <= user.balance) {
        user.balance -= amount;
        cout << "Withdrawal successful. New balance: R" << user.balance << "\n\n";
    } else {
        cout << "Invalid amount or insufficient balance.\n\n";
    }
    cin.ignore();
}

void checkBalance() {
    cout << "Your balance is: R" << user.balance << "\n\n";
}

int main() {
    cout << "Mini Banking System\n";
    createAccount();
    int choice = 0;
    do {
        cout << "Menu:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\\n');
            cout << "Please enter a number: ";
        }
        cin.ignore();
        switch (choice) {
            case 1: deposit(); break;
            case 2: withdraw(); break;
            case 3: checkBalance(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n\n";
        }
    } while (choice != 4);
    return 0;
}
