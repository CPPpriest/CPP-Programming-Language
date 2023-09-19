#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Account.h"
#include "PremiumAccount.h"

// Suppose the imaginary government in this example wants to make a stimulus
// payment of 10.00 to all accounts. We will do it by accessing all accounts
// via the static getAccount() function with the account numbers. To keep the
// example simple, we assume that there are always only two accounts with
// account numbers 1 and 2.

void payStimulus()
{
    for(int i = 1; i <= 2; i++)
    {
        Account *acctPtr = Account::getAccount(i);
        acctPtr->deposit(10.f); // Calls the right function since deposit() is virtual.
        //we want it to call appopriate function depending on class type,
        //not the default base class function
        //so we make the base class function virtual

        /* correct function must be selected according to INSTANCE TYPE
         * which is not known at compile time.
         * it is selected on run-time.
         */
    }
}


class UltraAccount : public PremiumAccount
{
    public:
        UltraAccount(string nm, float th) : PremiumAccount(nm,th)
        {
        }

        void deposit(float amount) override{    // "override" keyword is a safety feaature.
                                                // in case of forgotten "virtual" in the decleration.
            mLog += "ultra deposit\n";
            mBalance += amount;
        }
};


int main()
{
    /*
    Account alicesAccount("Alice");
    PremiumAccount bobsAccount("Bob", 5.f);
    */
    UltraAccount samsAccount("Sam", 13.f);
    samsAccount.deposit(14.f); // PremiumAcount::deposit()
    samsAccount.printDetails();


    /*
    payStimulus();

    alicesAccount.printDetails();
    bobsAccount.printDetails();
    */

    return 0;
}
