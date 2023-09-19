//
// Middle East Technical University
// Dept. of Computer Engineering
//
// CENG 213 - Data Structures
// Dr. Hakan YILDIZ
// hakan@ceng.metu.edu.tr
//
// Not to be reshared without permission.
//

// ***********************
// *** HEADER-SOURCE PAIRS
// ***********************

// This particular file is the source file for the Account class. This file
// only contains:
//     - The definition of the class' static fields. (No need to define the
//       instance fields)
//     - The definition of the class' instance and static functions.
//     - Any dependencies needed by these definitions.

// Usually the first line for the class source file is an #include directive
// for the class header file. Including the declarations is necessary, one
// cannot implement any class members that is not declared in the class. In
// other words, the declarations fix what the class is, and the class cannot be
// extended in any way. (It can be extended as another class as we will see
// later though.)
#include "Account.h"

// Coding Suggestion: It is a good idea to sort #include/using statements
//                    alphabetically.

#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <sstream>
using std::ios_base;
using std::stringstream;

#include <string>
// It is perfectly fine to write ``using'' in the source file. No other file
// would normally include this particular file, it would be unconventional to
// include a .cpp file.
using std::string;
using std::to_string;

// This function is only used by our function implementations. There is no
// need to put the declaraion of this function into the header file, as we do
// not expect other code to use it.
string f2s(float f)
{
    stringstream ss;
    ss.precision(2);
    ss.setf(ios_base::fixed);
    ss << f;
    return ss.str();
}

// When we ``define'' the member functions, we need to use their fully
// qualified name, using the class name as a prefix followed by ::.
void Account::deposit(float amount)
{        
    balance += amount;
    log += "deposit(" + f2s(amount) + ")\n";
}

bool Account::withdraw(float amount)
{
    if (balance >= amount)
    {
        balance -= amount;
        log += "withdraw(" + f2s(amount) + ")\n";
        
        return true;
    }
    else
    {
        return false;
    }
}

bool Account::transferTo(Account &targetAccount, float amount)
{
    if (balance >= amount)
    {
        balance -= amount;
        targetAccount.balance += amount;
        
        log += "transferTo("
               + to_string(targetAccount.accountNumber)
               + ", "
               + f2s(amount)
               + ")\n";
        
        targetAccount.log += "transferFrom("
                             + to_string(accountNumber)
                             + ", "
                             + f2s(amount)
                             + ")\n";
        
        return true;
    }
    else
    {
        return false;
    }
}

void Account::printDetails() const
{
    cout << "**** ACCOUNT DETAILS ****" << endl;
    cout << "Account Memory Address: " << this << endl;
    cout << "Account Number: " << this->accountNumber << endl;
    cout << "Owner Name: " << this->ownerName << endl;
    cout << "Balance: " << f2s(this->balance) << endl;
    cout << "Transactions:" << endl;
    cout << this->log << endl;
}

Account::Account(string oName)
{
    log = "";
    balance = 0.0f;
    accountNumber = nextAccountNumber;
    ownerName = oName;

    nextAccountNumber++;
    
    accounts[accountNumber] = this;
    
    cout << ownerName << "'s account is constructed." << endl;
}

Account::Account(string oName, float initialDeposit)
{
    log = "initialDeposit(" + f2s(initialDeposit) + ")\n";
    balance = initialDeposit;
    accountNumber = nextAccountNumber;
    ownerName = oName;
    
    nextAccountNumber++;
    
    accounts[accountNumber] = this;
    
    cout << ownerName
         << "'s account is constructed with initial balance "
         << f2s(initialDeposit)
         << "."
         << endl;
}

// The following is the implementation of the static Account::getAccount
// function. When defining static functions outside the class (after declaring
// in the class), we do NOT use the static keyword in front of the function
// prototype.

/* static */ Account * Account::getAccount(int accountNumber)
{
    return accounts[accountNumber];
}

Account::~Account()
{
    accounts.erase(accountNumber);
    
    cout << ownerName << "'s account is destroyed." << endl;
}

// The definitions for the static fields of the Account class.
int Account::nextAccountNumber = 1;
map<int, Account *> Account::accounts;
