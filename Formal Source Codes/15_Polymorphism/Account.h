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

// ****************
// *** POLYMORPHISM
// ****************

// We use the same Account and PremiumAccount classes that we used in our last
// example, with the following changes:
// - The deposit() function in Account is now is declared as a ``virtual''
//   function.
// - The deposit() function in PremiumAccount includes an ``override''
//   specifier.

#pragma once

#include <string>
#include <map>

class Account
{
    private:
        int mAccountNumber;
        std::string mOwnerName;

        static int sNextAccountNumber;
        static std::map<int, Account *> sAccounts;

    protected:
        float mBalance;
        std::string mLog;

    public:
        Account(std::string oName);
        Account(std::string oName, float initialDeposit);
        bool withdraw(float amount);
        bool transferTo(Account &targetAccount, float amount);
        void printDetails() const;
        ~Account();

        // The ``virtual'' keyword implies that deposit() is a ``virtual
        // function''/``virtual method'', and its behavior can be
        // ``overridden'' in a child class.
        virtual void deposit(float amount);

        Account(const Account &) = delete;
        Account & operator=(const Account &) = delete;

        static Account * getAccount(int accountNumber);
};


