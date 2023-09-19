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



struct Account
{
    int accountNumber;
    float balance;
    string ownerName;
    string log;
};



void deposit(Account &a, float amount )
{
    a.balance += amount;
    a.log += "deposit (" + f2s(amount) + ")\n";
}



bool withdraw(Account &a, float amount )
{
    if(a.balance < amount)
        return false;
    else
    {
        a.balance -= amount;
        a.log += "withdraw (" + f2s(amount) + ")\n";
        return true;
    }
}

//Deposit and withdraw are ABSTRACTIONS
//They are the interface that are used to easily manipulate data.

int main() {
    Account alicesAccount = {1, 2.f, "Alice", ""};
    deposit(alicesAccount, 103.4);
    withdraw(alicesAccount, 25);
    cout << alicesAccount.log << endl;
    return 0;
}







