#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;
using std::to_string;

#include <stdexcept>

class TaxCollectionException : public std::exception {};

class InsufficientFundsException : public TaxCollectionException
{
    public:
        InsufficientFundsException(float balance, float withdraw)
                :   mBalance(balance),
                    mWithdrawAmount(withdraw),
                    mWhat("Insufficient funs of" + to_string(balance) + " upon withdrawal of" + to_string(withdraw) + ".")
        {

        }
        const char* what() const noexcept
        {
            //called when an exception is thrown.
            //throw...; //throws an exceptio again -->> results in a complicated process
            //and if throws its own type -->> inf. loop

            //to avoid these kind of processes -->> define the method as 'noexcept'
            //which constrains the definition, not allowing to throw exceptions
            return mWhat.c_str();
        }

        float getBalance()
        {
            return mBalance;
        }

    private:
        float mBalance;
        float mWithdrawAmount;
        string mWhat;
};


class AccountNotFoundException : public TaxCollectionException {};





class SimpleAccount
{
    private:
        float mBalance;

        static int sNextAccountNumber;
        static map<int, SimpleAccount*> sAccounts;

    public:
        SimpleAccount(float initialBalance) : mBalance(initialBalance)
        {
            sAccounts[sNextAccountNumber++] = this;
        };

        void deposit(float amount) { mBalance += amount; };

        void withdraw(float amount)
        {
            if (mBalance < amount)
            {
                throw InsufficientFundsException(mBalance,amount);
            }
            else
            {
                mBalance -= amount;
            }
        }

        static SimpleAccount * getAccount(int accountNumber)
        {
            if (sAccounts.find(accountNumber) == sAccounts.end())
            {
                throw AccountNotFoundException();
            }
            else
            {
                return sAccounts[accountNumber];
            }
        }


};

/*static*/ int SimpleAccount::sNextAccountNumber = 1;
/*static*/ map<int, SimpleAccount*> SimpleAccount::sAccounts;

void collectTax(int accountNumber, float amount)
{
    SimpleAccount *a = SimpleAccount::getAccount(accountNumber);
    a->withdraw(amount);
}

void collectTaxes()
{
    for (int i = 1; i <= 4; i++)
    {
        try
        {
            collectTax(i, 10.f);
        }
        //due to class hierarchy, we can catch a base class exception
        //and all derived exceptions will be catched.
        //special implementation (overriden method calls) will be called
        //depending on child class

        catch(TaxCollectionException &e) //Now, catches exceptions of TaxCollectionException or its derived classes
        {
            std::cerr << "Some exception was caught." << endl;
        }

    }
}

int main()
{
    SimpleAccount alice(100.f);
    SimpleAccount bob(1.f);

    SimpleAccount * charlie = new SimpleAccount(50.f);

    //collectTaxes();
    /* if an exception is thrown here, during the call of collectTaxes
     * program crashes. Before termination calls the destructor of alice and bob.
     *
     * BUT, charlie is simply a pointer, so dynamic memory becomes garbage
     * resulting in a memory leak.
     *
     * instead, use a try catch block just to deallocate charlie and avoid memory leak!
     */

    try
    {
        collectTaxes();
    }
    catch(...)
    {
        delete charlie;

        throw;
        /* program is wanted to deallocate charlie and abort
         * in order to continue unwinding process (instead of returning),
         * we throw the exception again, which is not caught and resulting in termination
         */
    }

    delete charlie; //if program is successful, we still need to deallocate dynamic memory.

    //simply define two pieces to deallocate dyanmic memory:
    //  -one for the exception situation
    //  -one for the non-exception situation


    return 0;
}


