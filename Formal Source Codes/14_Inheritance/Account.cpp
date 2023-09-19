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

// ***************
// *** INHERITANCE
// ***************

// We use the same Account class that we used in our previous
// examples, with the following changes:
//     - The instance and the static variable names have been prefixed with "m"
//       and "s" respectively.
//     - Initializer lists are used to initialize the instance fields.
//     - The fields mLog and mBalance have been moved under a ``protected''
//       access modifier.

#include "Account.h"

#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <sstream>
using std::ios_base;
using std::stringstream;

#include <string>
using std::string;
using std::to_string;

string f2s(float f)
{
    stringstream ss;
    ss.precision(2);
    ss.setf(ios_base::fixed);
    ss << f;
    return ss.str();
}

Account::Account(string oName) : mAccountNumber(sNextAccountNumber),
                                 mOwnerName(oName),
                                 mBalance(0.0f),
                                 mLog("")
{
    sNextAccountNumber++;

    sAccounts[mAccountNumber] = this;

    cout << mOwnerName << "'s account is constructed." << endl;
}

Account::Account(string oName, float initialDeposit)
    : mAccountNumber(sNextAccountNumber),
      mOwnerName(oName),
      mBalance(initialDeposit),
      mLog("initialDeposit(" + f2s(initialDeposit) + ")\n")
{
    sNextAccountNumber++;

    sAccounts[mAccountNumber] = this;

    cout << mOwnerName
         << "'s account is constructed with initial balance "
         << f2s(initialDeposit)
         << "."
         << endl;
}

void Account::deposit(float amount)
{        
    mBalance += amount;
    mLog += "deposit(" + f2s(amount) + ")\n";
}

bool Account::withdraw(float amount)
{
    if (mBalance >= amount)
    {
        mBalance -= amount;
        mLog += "withdraw(" + f2s(amount) + ")\n";
        
        return true;
    }
    else
    {
        return false;
    }
}

bool Account::transferTo(Account &targetAccount, float amount)
{
    if (mBalance >= amount)
    {
        mBalance -= amount;
        targetAccount.mBalance += amount;
        
        mLog += "transferTo("
                 + to_string(targetAccount.mAccountNumber)
                 + ", "
                 + f2s(amount)
                 + ")\n";

        targetAccount.mLog += "transferFrom("
                               + to_string(mAccountNumber)
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
    cout << "Account Number: " << this->mAccountNumber << endl;
    cout << "Owner Name: " << this->mOwnerName << endl;
    cout << "Balance: " << f2s(this->mBalance) << endl;
    cout << "Transactions:" << endl;
    cout << this->mLog << endl;
}

Account::~Account()
{
    sAccounts.erase(mAccountNumber);
    
    cout << mOwnerName << "'s account is destroyed." << endl;
}

/*static*/ int Account::sNextAccountNumber = 1;

/*static*/ map<int, Account *> Account::sAccounts;

/*static*/ Account * Account::getAccount(int accountNumber)
{
    return sAccounts[accountNumber];
}
