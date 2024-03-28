#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;
using std::to_string; // primal types to string type


#include <stdexcept>

//unwinding of the stack: rolling stack back until the exception is catched (or termination)
//exception handling -->> done by exception handling code,
//try catch blocks

class InsufficientFundsException : public std::exception
{
    public:
        InsufficientFundsException(float balance, float withdraw)
                :   mBalance(balance),
                    mWithdrawAmount(withdraw),
                    mWhat("Insufficient funs of" + to_string(balance) + " upon withdrawal of" + to_string(withdraw) + ".")
        {

        }

        const char* what() const noexcept //returns a human readable message for the exception
        {
            return mWhat.c_str();   //c_str() is a method of string class
        }


    private:
    //since this is a class, it can store data inside.

        float mBalance;
        float mWithdrawAmount;
        string mWhat;
};


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
                return nullptr;
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
    for (int i = 1; i <= 2; i++)
    {
        try
        {
            collectTax(i, 10.f);
        }
        catch(...) //==> all type of exceptions
        {
            //cout << "Exception while collecting tax from " << i << "." << endl;
            std::cerr << "Exception while collecting tax from " << i << "." << endl;
            //sent to standard error stream instead of output stream.
        }


    }
}


int main()
{
    SimpleAccount alice(100.f);
    SimpleAccount bob(1.f);

    collectTaxes();

    return 0;
}

/* try catch blocks handle the exception and execution continues.
 *
 * output:
 *      Exception while collecting tax from 2.
 *
 */
