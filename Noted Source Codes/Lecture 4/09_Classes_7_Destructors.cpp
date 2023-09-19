#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;

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
//-----------------------------------//
#include<map>
using std::map;


class Account
{
private:
    int accountNumber;  // "data member" or "data field"
    float balance;
    string ownerName;
    string log; //instance member

    static map<int, Account*> accounts; //static member

public:
    Account(int acctNum, float initialBalance, string owner){
        accountNumber = acctNum;
        balance = initialBalance;
        ownerName = owner;
        log += "initial balance (" + f2s(initialBalance) + ")\n";

        accounts[accountNumber] = this;

        cout << "Account of " << owner << " is constructed." <<endl;
    }

    ~Account()
    {
        cout << "Account of " << ownerName << " is destructed." <<endl;
        accounts.erase(accountNumber);
    }

    Account(const Account &other)=delete;
    Account& operator=(const Account &other)=delete;

    void deposit(float amount ) // "method"
    {
        balance += amount;
        log += "deposit (" + f2s(amount) + ")\n";
    }

    bool withdraw(float amount )
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

    bool transferTo(Account &target, float amount)
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

    void printLog()
    {
        cout << log << endl;
    }

    void printDetails()
    {
        cout << "ACCOUNT DETAILS" << endl;
        cout << "Address of the account: " << this << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Owner: " << ownerName << endl;
        cout << "Balance: " << balance << endl;
        cout << "Log: " << log << endl;
    }

    static Account * getAddress(int acctNum){
        return accounts[acctNum];
    }
};


map<int, Account*> Account::accounts;







int main() {
    Account alicesAccount(17, 2.f, "Alice");
    Account bobsAccount(31, 8.f, "Bob");
    //Account::getAddress(17) -> printDetails();

    cout << "----" << endl;
    Account(3, 5.f, "someone").printDetails();
    //An account created without an identifier
    //cannot be used again. As a result, constructed and destructed at the same line
    cout << "----" << endl;

    // accounts with identifiers -->> destroyed at the end of scope
    // without identifier -->> destroyed at the same line

    return 0;
}







