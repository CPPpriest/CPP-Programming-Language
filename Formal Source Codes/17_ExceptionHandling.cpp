//
// Middle East Technical University
// Dept. of Computer Engineering
//
// CENG 213 - Data Structures
// Dr. Hakan YILDIZ
// hakan@ceng.metu.edu.tr
//
// Not to be reshared without permission.
//

// **********************
// *** EXCEPTION HANDLING
// **********************

#include <iostream>
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;
using std::to_string;

// Many modern languages, including C++, implement a mechanism called
// ``exception handling'' that offers the programmers a systematic way to deal
// with run-time errors. According to this mechanism, a run-time error is
// supposed to construct an object called an ``exception'' and ``throw'' (or
// ``raise'') it. When an exception is thrown, it will abort the functions in
// the call stack, in callee to caller order, until a piece of code ``catches''
// the exception. (This process is also called the ``unwinding'' of the call
// stack.) The catcher code, also called the ``exception handler'', can then
// take any necessary action to deal with the error. In some cases, the
// exception handler can ``rethrow'' the caught exception or throw a new brand
// new exception. If an exception is not caught by any exception handler, then
// it crashes the program, usually printing a message to the console.
//
// One should pay attention to the fact that the unwinding of the stack implies
// the premature abort of the functions and a portion of the functions' logic is
// not run. Luckily, this excludes the destructors of the local variables or
// temporary objects. Any object locally allocated in a function will be
// properly destroyed even if an exception is thrown during the function
// execution. Of course, dynamic objects allocated with ``new'' are not local
// objects. Having dynamic objects in a function may actually force the
// programmer to write a rethrowing exception handler, just to clean the dynamic
// objects properly.

// Conventionally, all exception objects are supposed to (directly or
// indirectly) derive from the ``std::exception'' class, defined in the
// ``stdexcept'' header.
#include <stdexcept>

// The following class represents an exception that is thrown when a bank
// account has insufficient funds for a withdraw operation.
class InsufficientFundsException : public std::exception
{
    private:
        // Member variables in exceptions allow us to store detailed information
        // about the exception, which can queried by the exception handler.
        const float mWithdrawAmount;
        const float mBalance;
        const string mWhat; // The message we want to print if the exception is
                            // not caught.

    public:
        InsufficientFundsException(float withdrawAmount, float balance)
            : mWithdrawAmount(withdrawAmount),
              mBalance(balance),
              mWhat("Unable to withdraw " + to_string(withdrawAmount) +
                    " from account with balance " + to_string(balance) + ".")
        {
        }

        float getWithdrawAmount() const { return mWithdrawAmount; }
        float getBalance() const { return mBalance; }

        // This is an override of the ``what()'' function of the std::exception
        // class. If no code catches this particular exception, then the C-style
        // string returned by this function is printed after the program is
        // terminated. C++ requires that this function does not itself throw any
        // exceptions. Therefore a ``noexcept'' specifier is mentioned. The
        // compiler will prevent any code that throws an exception inside this
        // function.
        const char * what() const noexcept override final
        {
            return mWhat.c_str();
        }
};

// The following class represents an exception that is thrown when a bank
// account is not found for a particular account number.
class AccountNotFoundException : public std::exception
{
    private:
        const int mAccountNumber;
        const string mWhat;

    public:
        AccountNotFoundException(int accountNumber) :
              mAccountNumber(accountNumber),
              mWhat("Account " + to_string(accountNumber) + " does not exist.")
        {
        }

        int getAccountNumber() const { return mAccountNumber; }

        const char * what() const noexcept override final
        {
            return mWhat.c_str();
        }
};

// A simplified version of the Account class from our previous examples. Only
// contains a balance and a static map to access accounts by account number.
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

        // Instead of returning a Boolean status code, we now return void for
        // the withdraw function. If there is not sufficient balance for the
        // withdraw operation, an InsufficientFundsException will be raised.
        void withdraw(float amount)
        {
            if (mBalance < amount)
            {
                // Traditionally, we throw exceptions by creating a temporary
                // instance. However, the stack unwinding mechanism takes the
                // ownership of this object and thus the object will continue
                // to exist until the whole exception handling process is
                // finished.
                throw InsufficientFundsException(amount, mBalance);
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
                // A similar exception thrown for not finding any accounts for a
                // particular account number.
                throw AccountNotFoundException(accountNumber);
            }
            else
            {
                return sAccounts[accountNumber];
            }
        }
};

/*static*/ int SimpleAccount::sNextAccountNumber = 1;
/*static*/ map<int, SimpleAccount*> SimpleAccount::sAccounts;

// This function tries to withdraw a given amount of tax from the account whose
// account number is given. It can fail in two ways:
//     - There is no account with the given number. Then, an
//       AccountNotFoundException is raised by the SimpleAccount::getAccount()
//       function.
//     - There are insufficient funds in the account. Then, an
//       InsufficientFundsException will be raised by the
//       SimpleAccount::withdraw() function
// Both exceptions will abort this function immediately and start unwinding
// the stack until an exception handler catches them.
//
// In general, it is a good idea to document the exception types that can be
// thrown a function.
void collectTax(int accountNumber, float amount)
{
    SimpleAccount *a = SimpleAccount::getAccount(accountNumber);
    a->withdraw(amount);
}

// Below, you see three versions of a function that attempts to collect taxes
// from all potential accounts in the system. For simplicity, we assume that
// these are the accounts numbered from 1 to 3. It is possible that an account
// does not exist or has an insufficient balance.

// [A] This version of the function handles all ``exceptions'' by ignoring them,
// yet printing a message.
void collectTaxes_IgnoreAllExceptions()
{
    for (int i = 1; i <= 3; i++)
    {
        // When one wants to write an exception handler, he/she should specify
        // the code whose exceptions are to be handled. This is done by putting
        // the code of concern into a ``try'' block. All try blocks must be
        // followed by at least one ``catch'' block that contains the exception
        // handling code for the try block.
        try
        {
            collectTax(i, 10.f);
            // If the call to collectTax() throws an exception, then any code
            // following it in the try block will be aborted.
        }
        // The catch block consists of two parts:
        // - A part written in parentheses that specifies what kind of
        //   exceptions are to be caught by this catch block. C++ respects the
        //   IS-A relation introduced by inheritance for this purpose. Since
        //   InsufficientFundsException and AccountNotFoundException are both
        //   std::exceptions, the following catch block catches exception of
        //   both types (and any other exception type that we do not know yet,
        //   as long as the type derives from std::exception). This part can
        //   also declare a variable that stores the caught exception. (In our
        //   example, it is ``e''.) To avoid copy construction, this variable is
        //   usually declared as a reference.
        // - A part written in curly braces that contains the exception handling
        //   code.
        catch (std::exception &e)
        {
            cout << "Ignoring the following exception:" << endl;
            cout << "    Exception Message: " << e.what() << endl;
        }

        // If an exception is handled by the catch block, then the code will
        // continue running here, after running the catch block's code.
    }
}

// [B] This version of the function handles InsufficientFundsExceptions and
// AccountNotFoundExceptions, again by ignoring them. Any other exception,
// however, will escape this function.
void collectTaxes_IgnoreBothExceptions()
{
    for (int i = 1; i <= 3; i++)
    {
        try
        {
            collectTax(i, 10.f);
        }
        // It is possible to define more than one catch block after a try block
        // to handle multiple types of exceptions, each with a different logic.
        catch (InsufficientFundsException &e)
        {
            cout << "Ignoring the following InsufficientFundsException:" << endl;
            cout << "    Exception Message: " << e.what() << endl;
        }
        catch (AccountNotFoundException &e)
        {
            cout << "Ignoring the following AccountNotFoundException:" << endl;
            cout << "    Exception Message: " << e.what() << endl;
        }
    }
}

// [C] This version of the function handles only InsufficientFundsExceptions.
void collectTaxes_IgnoreInsufficientFundsException()
{
    for (int i = 1; i <= 3; i++)
    {
        try
        {
            collectTax(i, 10.f);
        }
        catch (InsufficientFundsException &e)
        {
            cout << "Ignoring the following InsufficientFundsException:" << endl;
            cout << "    Exception Message: " << e.what() << endl;
        }
    }
}

int main()
{
    SimpleAccount alice(100.f); // Account 1.
    SimpleAccount bob(1.f); // Account 2.
    // No account 3.

    try
    {
        cout << "Calling collectTaxes_IgnoreAllExceptions()" << endl;
        collectTaxes_IgnoreAllExceptions();
        cout << endl;

        cout << "Calling collectTaxes_IgnoreBothExceptions()" << endl;
        collectTaxes_IgnoreBothExceptions();
        cout << endl;

        cout << "Calling collectTaxes_IgnoreInsufficientFundsException()" << endl;
        collectTaxes_IgnoreInsufficientFundsException();
        cout << endl;
    }
    catch (std::exception &e)
    {
        // The AccountNotFoundException thrown inside the
        // ``collectTaxes_IgnoreInsufficientFundsException'' function will abort
        // that function and be caught by this catch block.
        cout << "Caught an exception in main(). "
             << "Rethrowing to crash the program." << endl;

        // Here, we ``rethrow'' the same exception object, which means the
        // object will continue unwinding the stack after making a temporary
        // stop here. Since the main() function is our entry point, there is no
        // caller code that can handle this exception. Consequently, the
        // exception is captured by the C++ runtime and causes the termination
        // of the program. The type of the exception and its what() message is
        // printed to the screen.
        throw;
    }

    return 0;
}
