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
Account::Account(){cout << "Account()" <<endl;}
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

Account::~Account()
{
    accounts.erase(accountNumber);

    cout << ownerName << "'s account is destroyed." << endl;
}

/*static*/ int Account::nextAccountNumber = 1;

/*static*/ map<int, Account *> Account::accounts;

/*static*/ Account * Account::getAccount(int accountNumber)
{
    return accounts[accountNumber];
}
