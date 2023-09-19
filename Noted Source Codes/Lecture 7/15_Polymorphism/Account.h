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

        /* Account instance have a funtion table
         * its instances contain a pointer to this table which is 8 byte.
         *
         * when a virtual function is added to the class, it now have two different tables
         * one default and one virtual function table
         * so it adds an extra pointer for the second table
         *
         * if its instance have 80 bytes without any virtual,
         * it will be 88 bytes after a virtual definition
         *
         * any other virtual function will be added to the table and the
         * virtual function table pointer will remain
         * so instance size is still 88bytes
         */

        // an instance would be 80 bytes.
        virtual void deposit(float amount); // an instance would be 88 bytes.
        //virtual void withdraw(float amount); // an instance would be 88 bytes.
        //virtual void closeAccount(float amount); // an instance would be 88 bytes.

        Account(const Account &) = delete;
        Account & operator=(const Account &) = delete;

        static Account * getAccount(int accountNumber);
};


