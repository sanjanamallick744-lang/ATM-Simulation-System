# Advanced ATM Simulation in C++

## 📌 Project Overview

The **Advanced ATM Simulation** is a console-based C++ project that simulates the basic operations of an Automated Teller Machine (ATM).

The project demonstrates **C++ programming, file handling, authentication, transaction management, and data persistence**. Account balance, PIN, and transaction records are stored in files so that important data is retained even after the program is closed.

## ✨ Features

* 🔐 4-digit PIN authentication
* 🔒 Maximum 3 login attempts
* 💰 Check account balance
* 💵 Withdraw money
* ➕ Deposit money
* 🔄 Transfer money
* 📋 Complete transaction history
* 🧾 Mini statement showing recent transactions
* 👤 Account holder details
* 🔑 Change PIN
* 💾 Persistent balance storage
* 💾 Persistent PIN storage
* 🕒 Transaction date and time recording
* 🚫 Daily withdrawal limit
* 💰 Maximum withdrawal limit per transaction
* 💵 Maximum deposit limit
* ✅ Input validation
* 🚪 Logout option

## 🛠️ Technologies Used

* **Language:** C++
* **Compiler:** Dev-C++ / g++
* **Concepts Used:**

  * Functions
  * File Handling
  * Loops
  * Conditional Statements
  * Switch Case
  * Strings
  * Arrays
  * References
  * Structures of modular programming
  * Date and Time
  * Input Validation

## 📂 Files Used

The program automatically creates and uses the following files:

```text
account.txt
pin.txt
transactions.txt
```

### account.txt

Stores the current account balance.

### pin.txt

Stores the user's current PIN.

### transactions.txt

Stores transaction records including:

* Transaction type
* Amount
* Remaining balance
* Date and time

## 🔑 Default Login

```text
Account Holder : Sanjana Mallick
Account Number : AC10001
Default PIN    : 1234
```

> The PIN can be changed from the ATM menu.

## 📋 Main Menu

```text
====================================
             ATM MAIN MENU
====================================
1. Check Balance
2. Withdraw Money
3. Deposit Money
4. Transfer Money
5. Transaction History
6. Mini Statement
7. Account Details
8. Change PIN
9. Logout
====================================
```

## 💰 Transaction Limits

| Transaction                        |      Limit |
| ---------------------------------- | ---------: |
| Maximum withdrawal per transaction | Rs. 10,000 |
| Daily withdrawal limit             | Rs. 20,000 |
| Maximum deposit                    | Rs. 50,000 |

## 🔄 Example Workflow

```text
Start Program
      ↓
Enter PIN
      ↓
Authentication
      ↓
ATM Main Menu
      ↓
Select Operation
      ↓
Perform Transaction
      ↓
Update Balance
      ↓
Save Transaction
      ↓
Return to Menu
      ↓
Logout
```

## 🖥️ Sample Output

```text
====================================
       WELCOME TO ATM SYSTEM
====================================
Account Holder: Sanjana Mallick
Account Number: AC10001

Enter your 4-digit PIN: 1234

Login successful!


====================================
             ATM MAIN MENU
====================================
Account: AC10001
------------------------------------
1. Check Balance
2. Withdraw Money
3. Deposit Money
4. Transfer Money
5. Transaction History
6. Mini Statement
7. Account Details
8. Change PIN
9. Logout
------------------------------------

Enter your choice: 1

====================================
             BALANCE
====================================
Available Balance: Rs. 5000.00
====================================
```

## 📚 Concepts Demonstrated

This project demonstrates practical implementation of:

* **File Handling:** Reading and writing account information
* **Authentication:** PIN-based login system
* **Data Persistence:** Saving balance and PIN between program executions
* **Transaction Management:** Recording deposits, withdrawals, and transfers
* **Input Validation:** Checking invalid amounts and PIN formats
* **Functions:** Dividing the program into reusable modules
* **Loops:** Managing login attempts and the ATM menu
* **Conditional Logic:** Validating transactions and account conditions
* **Date & Time:** Recording when transactions occur

## 🚀 Future Improvements

Possible future enhancements include:

* Multiple user accounts
* Database integration
* GUI-based ATM interface
* OTP verification
* Account creation and deletion
* Password/PIN encryption
* Interest calculation
* Bank statement generation
* Admin panel
* Receipt generation
* Automatic daily withdrawal reset

## 🎯 Learning Outcome

This project helped demonstrate how C++ can be used to build a practical **banking and authentication system** using file handling and modular programming.

It also provides a foundation for understanding concepts related to **secure authentication, transaction processing, data storage, and basic cybersecurity**.

## 👩‍💻 Author

**Sanjana Mallick**

B.Tech CSIT — Cybersecurity

## 📄 License

This project is created for **educational and learning purposes**.
