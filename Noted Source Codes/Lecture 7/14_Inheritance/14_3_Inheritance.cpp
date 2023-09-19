#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Account.h"


class PremiumAccount : public Account   //inherets from Account class
{
    private:
            float mThreshold;

    public:
        // constructor call to Account constructor function,
        // initializes the data members inherited from base class
        PremiumAccount(string ownerName, float threshold) : Account(ownerName), mThreshold(threshold)
        {

        }

        float getThreshold() const
        {
            return mThreshold;
        }


        void deposit(float amount)  // "override" (Not Technically correct! Since No polymorphism involved.)
        {
            mBalance += amount;
            mLog += "deposit\n";
            if(amount >= mThreshold)
            {
                mBalance += 1.f;
                mLog += "reward(1.f);\n";
            }

            //Now mBalance and mLog are protected members -->> accessible to subclass
        }

};


int main()
{
    Account alicesAccount("Alice");
    alicesAccount.deposit(10.f);
    alicesAccount.printDetails();

    cout << "---------------" <<endl;

    PremiumAccount bobsAccount("Bob", 20.f);



    bobsAccount.deposit(25.f); // PremiumAccount::deposit()
    ((Account*) &bobsAccount)->deposit(25.f); // Account::deposit()
    ((Account&)bobsAccount).deposit(25.f); // Account::deposit()
    bobsAccount.Account::deposit(25.f); // Account::deposit()


    //accountNumber of bob is 2, since it is the second created account.
    Account::getAccount(2) -> deposit(50.f); // Account::deposit()
    PremiumAccount::getAccount(2) -> deposit(50.f); // Account::deposit()
    //PremiumAccount::getAccount() is not overriden, so it returns Account *

    (  (PremiumAccount *) Account::getAccount(2) ) ->deposit(50.f); // PremiumAccount::deposit()
    //Account* is returned and casted to PremiumAccount*, then calls PremiumAccount's deposit function

    bobsAccount.printDetails();


    ( (PremiumAccount *) Account::getAccount(1) ) ->deposit(50.f);
    // Risky Move
    /*
     * alicesAccount -->> is not a PremiumAccount, doesnt have a threshold !
     * but compiler still makes a call to PremiumAccount::deposit()
     * compiler finds the corresponding memory block (location where threshold value supposed to be)
     * since this memory block is not allocated, there is either a runtime error or Garbage value
     * mostly, garbage value is used as threshold.
     */


    alicesAccount.printDetails();

    return 0;
}

