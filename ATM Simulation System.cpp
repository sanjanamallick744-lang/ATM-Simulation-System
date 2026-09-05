#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string BALANCE_FILE = "account.txt";
const string HISTORY_FILE = "transactions.txt";

// Load balance
double loadBalance()
{
    ifstream file(BALANCE_FILE.c_str());
    double balance = 5000.00;

    if (file)
    {
        file >> balance;
        file.close();
    }

    return balance;
}

// Save balance
void saveBalance(double balance)
{
    ofstream file(BALANCE_FILE.c_str());

    if (file)
    {
        file << fixed << setprecision(2) << balance;
        file.close();
    }
}

// Save transaction
void recordTransaction(string type, double amount, double balance)
{
    ofstream file(HISTORY_FILE.c_str(), ios::app);

    if (file)
    {
        file << fixed << setprecision(2);
        file << type << " : Rs. " << amount
             << " | Balance: Rs. " << balance << endl;

        file.close();
    }
}

// Show transaction history
void transactionHistory()
{
    ifstream file(HISTORY_FILE.c_str());
    string line;

    cout << "\n========== TRANSACTION HISTORY ==========\n";

    if (!file)
    {
        cout << "No transactions found.\n";
        return;
    }

    bool found = false;

    while (getline(file, line))
    {
        cout << line << endl;
        found = true;
    }

    if (!found)
        cout << "No transactions found.\n";

    file.close();
}

// Change PIN
void changePIN(string &pin)
{
    string oldPin, newPin, confirmPin;

    cout << "\nEnter current PIN: ";
    cin >> oldPin;

    if (oldPin != pin)
    {
        cout << "Incorrect PIN!\n";
        return;
    }

    cout << "Enter new 4-digit PIN: ";
    cin >> newPin;

    if (newPin.length() != 4)
    {
        cout << "PIN must contain exactly 4 digits.\n";
        return;
    }

    cout << "Confirm new PIN: ";
    cin >> confirmPin;

    if (newPin != confirmPin)
    {
        cout << "PINs do not match!\n";
        return;
    }

    pin = newPin;

    cout << "PIN changed successfully!\n";
}

// ATM menu
void atmMenu(string &pin)
{
    double balance = loadBalance();
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "           ATM MAIN MENU\n";
        cout << "====================================\n";
        cout << "1. Check Balance\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Deposit Money\n";
        cout << "4. Transaction History\n";
        cout << "5. Change PIN\n";
        cout << "6. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << fixed << setprecision(2);
                cout << "\nCurrent Balance: Rs. "
                     << balance << endl;
                break;

            case 2:
            {
                double amount;

                cout << "\nEnter withdrawal amount: Rs. ";
                cin >> amount;

                if (amount <= 0)
                {
                    cout << "Invalid amount!\n";
                }
                else if (amount > balance)
                {
                    cout << "Insufficient balance!\n";
                }
                else
                {
                    balance = balance - amount;

                    saveBalance(balance);
                    recordTransaction("Withdrawal", amount, balance);

                    cout << "Please collect your cash.\n";
                    cout << "Remaining Balance: Rs. "
                         << fixed << setprecision(2)
                         << balance << endl;
                }

                break;
            }

            case 3:
            {
                double amount;

                cout << "\nEnter deposit amount: Rs. ";
                cin >> amount;

                if (amount <= 0)
                {
                    cout << "Invalid amount!\n";
                }
                else
                {
                    balance = balance + amount;

                    saveBalance(balance);
                    recordTransaction("Deposit", amount, balance);

                    cout << "Amount deposited successfully!\n";
                    cout << "New Balance: Rs. "
                         << fixed << setprecision(2)
                         << balance << endl;
                }

                break;
            }

            case 4:
                transactionHistory();
                break;

            case 5:
                changePIN(pin);
                break;

            case 6:
                cout << "\nThank you for using the ATM!\n";
                cout << "Please take your card.\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);
}

int main()
{
    string pin = "1234";
    string enteredPin;

    cout << "====================================\n";
    cout << "       WELCOME TO ATM SYSTEM\n";
    cout << "====================================\n";

    // 3 login attempts
    for (int attempt = 1; attempt <= 3; attempt++)
    {
        cout << "\nEnter your 4-digit PIN: ";
        cin >> enteredPin;

        if (enteredPin == pin)
        {
            cout << "\nLogin successful!\n";

            atmMenu(pin);

            return 0;
        }
        else
        {
            cout << "Incorrect PIN!\n";

            if (attempt < 3)
            {
                cout << "Attempts remaining: "
                     << 3 - attempt << endl;
            }
        }
    }

    cout << "\nToo many incorrect attempts.\n";
    cout << "Your account has been temporarily locked.\n";

    return 0;
}
