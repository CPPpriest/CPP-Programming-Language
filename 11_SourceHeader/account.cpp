#include "Account.h"

#include <iostream>
using std::cout;
using std::endl;

#include<sstream>
using std::stringstream;
using std::ios_base;

string f2s(float f){
    stringstream ss;
    ss.precision(2);
    ss.setf(ios_base::fixed);
    ss << f;
    return ss.str();
}


// using statements (that omited in header file)
using std::string;
using std::map;



map<int, Account*> Account::accounts;	// Static member (accounts) DEFINITION


//Method implementations require -->> Fully Qualified Name
//They belong to the class

Account::Account(int acctNum, float initialBalance, string owner)
{
        accountNumber = acctNum;
        balance = initialBalance;
        ownerName = owner;
        log += "initial balance (" + f2s(initialBalance) + ")\n";

        accounts[accountNumber] = this;

        cout << "Account of " << owner << " is constructed." <<endl;
}

Account::~Account()	// Fully qualified name for destructor
{
        cout << "Account of " << ownerName << " is destructed." <<endl;
        accounts.erase(accountNumber);
}

void Account::deposit(float amount )
{
        balance += amount;
        log += "deposit (" + f2s(amount) + ")\n";
}

bool Account::withdraw(float amount )
{
        if(balance < amount)
            return false;
        else
	{
            balance -= amount;
            log += "withdraw (" + f2s(amount) + ")\n";
            return true;
        }
}

bool Account::transferTo(Account &target, float amount)
{
        if(balance >= amount){
            balance -= amount;
            target.balance += amount;

            log += "transfer(-" + f2s(amount) + ")\n";
            target.log += "transfer(+" + f2s(amount) + ")\n";
            return true;
        }
        else
            return false;
}

void Account::printLog()
{
        cout << log << endl;
}

void Account::printDetails()
{
        cout << "ACCOUNT DETAILS" << endl;
        cout << "Address of the account: " << this << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Owner: " << ownerName << endl;
        cout << "Balance: " << balance << endl;
        cout << "Log: " << log << endl;
}



static Account::Account * getAddress(int acctNum)	
{
        return accounts[acctNum];
}




int main() {
    Account alicesAccount(17, 2.f, "Alice");
    Account bobsAccount(31, 8.f, "Bob");
    
    return 0;
}







