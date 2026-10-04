#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

const string BALANCE_FILE = "account.txt";
const string PIN_FILE = "pin.txt";
const string HISTORY_FILE = "transactions.txt";

const double DAILY_LIMIT = 20000.00;
const double MAX_WITHDRAWAL = 10000.00;
const double MAX_DEPOSIT = 50000.00;

// Get current date and time
string getDateTime()
{
    time_t now = time(0);
    char *dt = ctime(&now);

    string result = dt;

    // Remove newline
    if (!result.empty() && result[result.length() - 1] == '\n')
        result.erase(result.length() - 1);

    return result;
}

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
    else
    {
        ofstream newFile(BALANCE_FILE.c_str());
        newFile << fixed << setprecision(2) << balance;
        newFile.close();
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

// Load PIN
string loadPIN()
{
    ifstream file(PIN_FILE.c_str());
    string pin = "1234";

    if (file)
    {
        file >> pin;
        file.close();
    }
    else
    {
        ofstream newFile(PIN_FILE.c_str());
        newFile << pin;
        newFile.close();
    }

    return pin;
}

// Save PIN
void savePIN(string pin)
{
    ofstream file(PIN_FILE.c_str());

    if (file)
    {
        file << pin;
        file.close();
    }
}

// Record transaction
void recordTransaction(string type, double amount, double balance)
{
    ofstream file(HISTORY_FILE.c_str(), ios::app);

    if (file)
    {
        file << "[" << getDateTime() << "] "
             << type
             << " | Amount: Rs. "
             << fixed << setprecision(2)
             << amount
             << " | Balance: Rs. "
             << balance
             << endl;

        file.close();
    }
}

// Show transaction history
void transactionHistory()
{
    ifstream file(HISTORY_FILE.c_str());
    string line;

    cout << "\n==============================================\n";
    cout << "              TRANSACTION HISTORY\n";
    cout << "==============================================\n";

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

// Show account details
void accountDetails(string name, string accountNumber, double balance)
{
    cout << "\n====================================\n";
    cout << "           ACCOUNT DETAILS\n";
    cout << "====================================\n";

    cout << "Account Holder : " << name << endl;
    cout << "Account Number : " << accountNumber << endl;

    cout << fixed << setprecision(2);
    cout << "Balance        : Rs. " << balance << endl;

    cout << "====================================\n";
}

// Check balance
void checkBalance(double balance)
{
    cout << "\n====================================\n";
    cout << "             BALANCE\n";
    cout << "====================================\n";

    cout << fixed << setprecision(2);
    cout << "Available Balance: Rs. "
         << balance << endl;

    cout << "====================================\n";
}

// Withdraw money
bool withdrawMoney(double &balance, double &dailyWithdrawn)
{
    double amount;

    cout << "\nEnter withdrawal amount: Rs. ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!\n";
        return false;
    }

    if (amount > MAX_WITHDRAWAL)
    {
        cout << "Maximum withdrawal per transaction is Rs. "
             << MAX_WITHDRAWAL << endl;
        return false;
    }

    if (amount > balance)
    {
        cout << "Insufficient balance!\n";
        return false;
    }

    if (dailyWithdrawn + amount > DAILY_LIMIT)
    {
        cout << "Daily withdrawal limit exceeded!\n";
        cout << "Daily limit: Rs. " << DAILY_LIMIT << endl;
        cout << "Already withdrawn today: Rs. "
             << dailyWithdrawn << endl;
        return false;
    }

    balance = balance - amount;
    dailyWithdrawn = dailyWithdrawn + amount;

    saveBalance(balance);
    recordTransaction("Withdrawal", amount, balance);

    cout << "\nPlease collect your cash.\n";

    cout << fixed << setprecision(2);
    cout << "Withdrawn Amount : Rs. " << amount << endl;
    cout << "Remaining Balance: Rs. " << balance << endl;

    return true;
}

// Deposit money
bool depositMoney(double &balance)
{
    double amount;

    cout << "\nEnter deposit amount: Rs. ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!\n";
        return false;
    }

    if (amount > MAX_DEPOSIT)
    {
        cout << "Maximum deposit allowed is Rs. "
             << MAX_DEPOSIT << endl;
        return false;
    }

    balance = balance + amount;

    saveBalance(balance);
    recordTransaction("Deposit", amount, balance);

    cout << "\nAmount deposited successfully!\n";

    cout << fixed << setprecision(2);
    cout << "Deposited Amount: Rs. " << amount << endl;
    cout << "New Balance    : Rs. " << balance << endl;

    return true;
}

// Transfer money
bool transferMoney(double &balance)
{
    string receiver;
    double amount;

    cout << "\nEnter receiver account number: ";
    cin >> receiver;

    if (receiver.length() < 5)
    {
        cout << "Invalid account number!\n";
        return false;
    }

    cout << "Enter transfer amount: Rs. ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!\n";
        return false;
    }

    if (amount > balance)
    {
        cout << "Insufficient balance!\n";
        return false;
    }

    balance = balance - amount;

    saveBalance(balance);

    recordTransaction(
        "Transfer to Account " + receiver,
        amount,
        balance
    );

    cout << "\nTransfer successful!\n";
    cout << "Receiver Account: " << receiver << endl;

    cout << fixed << setprecision(2);
    cout << "Transferred     : Rs. " << amount << endl;
    cout << "Remaining Balance: Rs. " << balance << endl;

    return true;
}

// Change PIN
void changePIN(string &pin)
{
    string oldPin;
    string newPin;
    string confirmPin;

    cout << "\nEnter current PIN: ";
    cin >> oldPin;

    if (oldPin != pin)
    {
        cout << "Incorrect current PIN!\n";
        return;
    }

    cout << "Enter new 4-digit PIN: ";
    cin >> newPin;

    if (newPin.length() != 4)
    {
        cout << "PIN must contain exactly 4 digits.\n";
        return;
    }

    // Check whether PIN contains only digits
    int i;

    for (i = 0; i < 4; i++)
    {
        if (newPin[i] < '0' || newPin[i] > '9')
        {
            cout << "PIN must contain only digits.\n";
            return;
        }
    }

    cout << "Confirm new PIN: ";
    cin >> confirmPin;

    if (newPin != confirmPin)
    {
        cout << "PINs do not match!\n";
        return;
    }

    pin = newPin;

    savePIN(pin);

    cout << "PIN changed successfully!\n";
}

// Mini statement
void miniStatement()
{
    ifstream file(HISTORY_FILE.c_str());

    string lines[5];
    string line;
    int count = 0;

    if (!file)
    {
        cout << "\nNo transactions available.\n";
        return;
    }

    while (getline(file, line))
    {
        lines[count % 5] = line;
        count++;
    }

    file.close();

    cout << "\n==============================================\n";
    cout << "               MINI STATEMENT\n";
    cout << "==============================================\n";

    if (count == 0)
    {
        cout << "No transactions found.\n";
        return;
    }

    int start;

    if (count > 5)
        start = count - 5;
    else
        start = 0;

    int i;

    for (i = start; i < count; i++)
    {
        cout << lines[i % 5] << endl;
    }

    cout << "==============================================\n";
}

// ATM Menu
void atmMenu(
    string &pin,
    string name,
    string accountNumber
)
{
    double balance = loadBalance();
    double dailyWithdrawn = 0.00;

    int choice;

    do
    {
        cout << "\n\n====================================\n";
        cout << "             ATM MAIN MENU\n";
        cout << "====================================\n";

        cout << "Account: " << accountNumber << endl;

        cout << "------------------------------------\n";
        cout << "1. Check Balance\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Deposit Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Transaction History\n";
        cout << "6. Mini Statement\n";
        cout << "7. Account Details\n";
        cout << "8. Change PIN\n";
        cout << "9. Logout\n";
        cout << "------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                checkBalance(balance);
                break;

            case 2:
                withdrawMoney(balance, dailyWithdrawn);
                break;

            case 3:
                depositMoney(balance);
                break;

            case 4:
                transferMoney(balance);
                break;

            case 5:
                transactionHistory();
                break;

            case 6:
                miniStatement();
                break;

            case 7:
                accountDetails(
                    name,
                    accountNumber,
                    balance
                );
                break;

            case 8:
                changePIN(pin);
                break;

            case 9:
                cout << "\nLogging out...\n";
                cout << "Thank you for using the ATM!\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
                cout << "Please select a valid option.\n";
        }

    } while (choice != 9);
}

// Main
int main()
{
    string name = "Sanjana Mallick";
    string accountNumber = "AC10001";

    string pin;
    string enteredPin;

    pin = loadPIN();

    cout << "====================================\n";
    cout << "       WELCOME TO ATM SYSTEM\n";
    cout << "====================================\n";

    cout << "Account Holder: " << name << endl;
    cout << "Account Number: " << accountNumber << endl;

    // Three login attempts
    int attempt;

    for (attempt = 1; attempt <= 3; attempt++)
    {
        cout << "\nEnter your 4-digit PIN: ";
        cin >> enteredPin;

        if (enteredPin == pin)
        {
            cout << "\nLogin successful!\n";

            atmMenu(
                pin,
                name,
                accountNumber
            );

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

    cout << "\n====================================\n";
    cout << "        ACCOUNT TEMPORARILY LOCKED\n";
    cout << "====================================\n";

    cout << "Too many incorrect attempts.\n";
    cout << "Please try again later.\n";

    return 0;
}
