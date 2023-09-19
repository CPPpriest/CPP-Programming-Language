#pragma once

#include <string>
#include <map>

class Account
{
    private:
        int accountNumber;
        float balance;
        std::string log;
        std::string ownerName;

        static int nextAccountNumber;
        static std::map<int, Account *> accounts;

    public:
        Account();
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

