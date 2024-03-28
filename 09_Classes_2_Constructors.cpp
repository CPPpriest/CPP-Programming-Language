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

//Fundamental mechanisms of OOP paradigm:
/*  1) Abstraction
 *  2) Encapsulation
 *  3) Inheritance
 *  4) Polymorphism
 */


//Encapsulation: Restricting outside access to object members
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

//An instance of a class can access
//the private members of another instance of the same class.
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

//Deposit and withdraw are ABSTRACTIONS
//They are the interface that are used to easily manipulate data.
//Restricting access to private members only through methods -->> ENCAPSULATION



int main() {
    Account alicesAccount(1, 2.f, "Alice");
    Account bobsAccount(2, 8.f, "Bob");
    alicesAccount.transferTo(bobsAccount, 1);
    alicesAccount.printLog();


    Account charliesAccount = alicesAccount;//-->> Account charliesAccount(alicesAccount);
    //This is a call for copy constructor.
    //Just like default construct, compiler defines an implicit copy constructor
    //Shallow copy

    Account sindysAccount(1, 2.f, "Sindy");
    sindysAccount = alicesAccount;
    //This is an assignment operator and not a copy construct call
    //Since it is not done during initialization
    //An assignment operator must be defined
    return 0;
}







