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

class Account;  //forward-decleration (of the class)

map<int,Account*> accounts; //holds address of every account created,
//maps from integer to pointer



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

        //everytime an Account created, it is added to accounts dictionary
        accounts[accountNumber] = this;
        // key: accountNumber
        // value: this
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
        cout << "Address of the account: " << this << endl; //address of the instance
        cout << "Account Number: " << accountNumber << endl; // this -> accountNumber
        cout << "Account Owner: " << ownerName << endl; // this -> ownerName
        cout << "Balance: " << balance << endl; // this -> balance
    }
};


int main() {
    Account alicesAccount(17, 2.f, "Alice"); //instance
    Account bobsAccount(31, 8.f, "Bob"); //instance

    accounts[17]->printDetails(); // alicesAccount.printDetails();
    accounts[0]->printDetails(); // bobsAccount.printDetails();

    return 0;
}







