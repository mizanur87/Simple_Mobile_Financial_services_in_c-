#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class representing a user account
class UserAccount {
private:
    string phoneNumber;
    string accountHolder;
    double balance;

public:
    UserAccount(const string& phone, const string& holder, double initialBalance)
        : phoneNumber(phone), accountHolder(holder), balance(initialBalance) {}

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

// Function to find a user account by phone number
UserAccount* findAccountByPhoneNumber(vector<UserAccount>& accounts, const string& phoneNumber) {
    for (UserAccount& account : accounts) {
        if (account.getPhoneNumber() == phoneNumber) {
            return &account;
        }
    }
    return nullptr;
}

// Function to send money from one account to another
bool sendMoney(vector<UserAccount>& accounts, const string& senderPhone, const string& receiverPhone, double amount) {
    UserAccount* senderAccount = findAccountByPhoneNumber(accounts, senderPhone);
    UserAccount* receiverAccount = findAccountByPhoneNumber(accounts, receiverPhone);

    if (senderAccount && receiverAccount) {
        if (senderAccount->withdraw(amount)) {
            receiverAccount->deposit(amount);
            return true;
        } else {
            cout << "Insufficient funds in the sender's account." << endl;
        }
    } else {
        cout << "Invalid phone number." << endl;
    }
    return false;
}

// Function to display account balance
void displayBalance(const vector<UserAccount>& accounts, const string& phoneNumber) {
    UserAccount* account = findAccountByPhoneNumber(accounts, phoneNumber);

    if (account) {
        cout << "Account Holder: " << account->getAccountHolder() << endl;
        cout << "Phone Number: " << account->getPhoneNumber() << endl;
        cout << "Balance: BDT " << account->getBalance() << endl;
    } else {
        cout << "Invalid phone number." << endl;
    }
}

// Function to create a new user account
void createAccount(vector<UserAccount>& accounts) {
    string phoneNumber, accountHolder;
    double initialBalance;

    cout << "Enter your phone number: ";
    cin >> phoneNumber;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, accountHolder);
    cout << "Enter the initial balance: BDT ";
    cin >> initialBalance;

    accounts.emplace_back(phoneNumber, accountHolder, initialBalance);
    cout << "Account created successfully." << endl;
}

int main() {
    vector<UserAccount> accounts;
    accounts.emplace_back("017xxxxxxxx", "John Doe", 1000.0);
    accounts.emplace_back("018xxxxxxxx", "Jane Smith", 500.0);

    cout << "Welcome to the Financial Service System!" << endl;

    while (true) {
        cout << "1. Send Money" << endl;
        cout << "2. Check Balance" << endl;
        cout << "3. Create an Account" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string senderPhone, receiverPhone;
                double amount;
                cout << "Sender Phone Number: ";
                cin >> senderPhone;
                cout << "Receiver Phone Number: ";
                cin >> receiverPhone;
                cout << "Amount (BDT): ";
                cin >> amount;

                bool success = sendMoney(accounts, senderPhone, receiverPhone, amount);
                if (success) {
                    cout << "Money sent successfully." << endl;
                }
                break;
            }
            case 2: {
                string phoneNumber;
                cout << "Enter your phone number: ";
                cin >> phoneNumber;

                displayBalance(accounts, phoneNumber);
                break;
            }
            case 3:
                createAccount(accounts);
                break;
            case 4:
                cout << "Thank you for using the Financial Service System. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }
}
