#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Account.h"

//a special Accout that gets extra money as reward,
//if it exceeds a threshold
class PremiumAccount : public Account   //inherets from Account class
{
    //instance members (data and method) are directly inherited.
    //constructors,destructor of PremiumAccount is not directly inherited.
    //They do NOT works as PremiumAccount constructors,destructor

};


int main()
{
    Account alicesAccount("Alice");
    alicesAccount.deposit(10.f);
    alicesAccount.printDetails();

    //PremiumAccount bobsAccount; // -->> ?? Doesnt work for some reason -->> check

    return 0;
}

