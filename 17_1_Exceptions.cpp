#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;
using std::to_string; // primal types to string type


//for ease of use, exceptions are derived from a base class.
//it is the exception class frım stdexcept header


//class InsufficientFuncdsException{};
#include <stdexcept>

/*
 * std::exception class provides two virtual functions to be overriden:
 *      virtual const char* what() const noexcept;
 *      virtual ~exception() noexcept;
 */


class InsufficientFundsException : public std::exception
{
    public:
        InsufficientFundsException()
        {
        }

        const char* what() const noexcept //returns a human readable message for the exception
        {
            return "There are insufficent funds.";
        }


    private:
    //since this is a class, it can have members

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
                //throw takes an instance of an exception object

                throw InsufficientFundsException();


                //create a temporary instance of exception obj and throw it.
                /*
                 * when an exception is thrown:
                 * 1. it abortes the current function
                 * 2. aborts the caller function
                 * 3. aborts the caller of caller function....
                 * 4. if it is not catched during the procees,
                 *    it finally aborts main and terminate the program.
                 * 5. compiler looks for what message to print with termination
                 *
                 */
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
        collectTax(i, 10.f);
    }
}


int main()
{
    SimpleAccount alice(100.f);
    SimpleAccount bob(1.f);

    collectTaxes();

    return 0;
}


/*
 * output:
 *      terminate called after throwing an instance of 'InsufficientFundsException',
 *      what():  There are insufficent funds.
 *
 */


