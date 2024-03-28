#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;
using std::to_string;

#include <stdexcept>

class InsufficientFundsException : public std::exception
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
            return mWhat.c_str();
        }

    private:
        float mBalance;
        float mWithdrawAmount;
        string mWhat;
};



class TaxCollectionException : std::exception {};







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
        catch(...)
        {
            std::cerr << "Exception while collecting tax from " << i << "." << endl;

            //throw TaxCollectionException();   //-->>throws TaxCollectionException
            //throw;    //-->>throws catched exception(InsufficientFundsException)

            /* we can throw an exception here as well.
             * same way, if is is not catched, crushes the program.
             *
             *Similarly, we can throw the catched exception
             *simply by 'throw' without an exception instance
             */
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
