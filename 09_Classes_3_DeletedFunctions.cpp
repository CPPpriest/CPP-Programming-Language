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
class Account
{
private:
    int accountNumber;  // "data member" or "data field"
    float balance;
    string ownerName;
    string log;

public:
    //Constructor is a special abstraction
    //for initializing an object's members
    Account(int acctNum, float initialBalance, string owner){
        accountNumber = acctNum;
        balance = initialBalance;
        ownerName = owner;
        log += "initial balance (" + f2s(initialBalance) + ")\n";
    }

    //To eliminate implicit copy constructor and assignment defined by compiler,
    //We define copy constructor and assignment definitions:

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
};


int main() {
    Account alicesAccount(1, 2.f, "Alice");
    Account bobsAccount(2, 8.f, "Bob");
    alicesAccount.transferTo(bobsAccount, 1);
    alicesAccount.printLog();


    Account charliesAccount = alicesAccount;//-->> Account charliesAccount(alicesAccount);


    Account sindysAccount(1, 2.f, "Sindy");
    sindysAccount = alicesAccount;

    //implicit copy constructor and assignment are deleted.
    //as a result these two calls returns error.
    //they are deleted functions


    return 0;
}







