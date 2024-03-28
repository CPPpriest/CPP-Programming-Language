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

// ***************
// *** INHERITANCE
// ***************

// We use the same Account class that we used in our previous examples, with
// the following changes:
//     - The instance and the static variable names have been prefixed with "m"
//       and "s" respectively.
//     - Initializer lists are used to initialize the instance fields.
//     - The fields mLog and mBalance have been moved under a ``protected''
//       access modifier.

#pragma once

#include <string>
#include <map>

class Account
{
    private:
        int mAccountNumber;
        std::string mOwnerName;

        static int sNextAccountNumber;  // assigned 0 value
        static std::map<int, Account *> sAccounts;

    protected:
    // members that are accessible to subclasses
    // but NOT accessible in any other scope

        float mBalance;
        std::string mLog;
    //friend class PremiumAccount;
    /* only PremiumAccount class can access the private field
     * more precise; other inheritance classes cannot.
     * can be used an alternative to using protected
     * but it is more precise than protected.
     * all inheritance classes can access protected members (public inheritance)
     */


    public:
        Account(std::string oName);
        Account(std::string oName, float initialDeposit);
        void deposit(float amount);
        bool withdraw(float amount);
        bool transferTo(Account &targetAccount, float amount);
        void printDetails() const;
        ~Account();

        Account(const Account &) = delete;
        Account & operator=(const Account &) = delete;

        static Account * getAccount(int accountNumber);
};


