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


        void deposit(float amount)  // PremiumAccount::deposit
        {
            //mBalance += amount; //-->> mBalance is a private member of Account

            //deposit(amount);  // due to hiding mechanism -->> calls PremiumAccount::deposit (recursive call)

            Account::deposit(amount);

            if(amount >= mThreshold)
            {
                Account::deposit(1.f);
            }


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

    //bobsAccount is actually a reference to PremiumAccount instance,
    //it can be cast to Account reference

    bobsAccount.Account::deposit(25.f); // Account::deposit()



    bobsAccount.printDetails();

    return 0;
}

