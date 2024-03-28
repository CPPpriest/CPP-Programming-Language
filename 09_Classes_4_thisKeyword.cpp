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
    Account(int acctNum, float initialBalance, string owner){
        accountNumber = acctNum;
        balance = initialBalance;
        ownerName = owner;
        log += "initial balance (" + f2s(initialBalance) + ")\n";
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

    // 'this' keyword
    // automatically added by the compiler
    // member functions (methods) using this pointer: INSTANCE FUNCTIONS
    void printDetails() // printDetails(Account *this);
    {
        cout << "ACCOUNT DETAILS" << endl;
        cout << "Address of the account: " << this << endl; //address of the instance
        cout << "Account Number: " << accountNumber << endl; // this -> accountNumber
        cout << "Account Owner: " << ownerName << endl; // this -> ownerName
        cout << "Balance: " << balance << endl; // this -> balance
    }
};


int main() {
    Account alicesAccount(1, 2.f, "Alice"); //instance
    Account bobsAccount(2, 8.f, "Bob"); //instance

    alicesAccount.printDetails();
    //printDetails(&alicesAccount);

    cout << endl;

    bobsAccount.printDetails();
    //printDetails(&bobsAccount);
    return 0;
}







