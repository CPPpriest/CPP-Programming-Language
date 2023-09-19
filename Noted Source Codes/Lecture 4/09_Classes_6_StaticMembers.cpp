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

//defining accounts as global, violates the encapsulation mechanism
//map<int,Account*> accounts;

//so we define it as a class member
//Since 'instance' members created at every instantiation, we define it as STATIC



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

/*
    Account * getAddress(int acctNum){
        return accounts[acctNum];
    }
*/
    // a function that is used without an instance must be a static function
    // so it must be defined as static

    static Account * getAddress(int acctNum){
        return accounts[acctNum];
    }
};

/* in C++, 'map<int, Account*> accounts;' is just a decleration
 * it is not defined in the class
 * it must be explicitly defined outside of the class with the scope resolution
 * without static keyword (in global scope, static keyword hides the identifier from
 * other source files. (Not the intended purpose here)
 */
map<int, Account*> Account::accounts;



int main() {
    Account alicesAccount(17, 2.f, "Alice"); //instance
    Account bobsAccount(31, 8.f, "Bob"); //instance

    /*
     * accounts[17]->printDetails(); // alicesAccount.printDetails();
     * accounts[31]->printDetails(); // bobsAccount.printDetails();
     *
     * these will not work since accounts is private now
     */

    // a static member does not require an instance to call it
    // yet a scope resolution is required:  Account::getAddress(17);

    Account::getAddress(17) -> printDetails();

    return 0;
}

/*
 * if an instance function is called,
 * an instance must call it
 *
 * if a static function (method) is called,
 * no specific instance is required to call it,
 * but the scope of the function must be explicitly written,
 * which is achieved via scope resolution (::)
 *
 *
 * a static data is available without an instance,
 * the same way a method using only static member, can be called without an instance
 * so it is defined as a static method.
 * Otherwise, a non static method (instance method) requires an instance to be called.
 */









