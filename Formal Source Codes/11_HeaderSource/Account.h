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

// ***********************
// *** HEADER-SOURCE PAIRS
// ***********************

// In C++, the code for classes are often divided into two files:
//     - .h ``header'' file: Contains the declaration of the class only.
//     - .cpp ``source'' file: Contains the implementation of the class.
// The main exception to this rule are the class templates, whose code has to
// be present in the header file.

// This particular file is the header file for the Account class. This file
// only contains:
//     - The declaration of the class's instance and static fields.
//     - The declaration of the class's instance and static functions.
//     - Any dependencies needed by these declarations.

// In general, all headers should start with the preprocessor directive
// ``#pragma once'' so that the compiler avoids including this file more than
// once during the proper compilation of a single .cpp source file. This is a
// shorter alternative to the classical header guards and all modern compilers
// support it.
#pragma once

#include <string>
#include <map>

class Account
{
    private:
        int accountNumber;
        float balance;
        // It is often considered best practice not to use any ``using''
        // statements in the header. This is because the effects of ``using''
        // would then go beyond the header file and affect the source file that
        // includes the header file. (Recall, the compiler does not see which
        // part belongs to the headers and which part to the source. The
        // #include directive is preprocessed. So effectively, the compiler
        // sees the using directive inside the preprocessed source and it would
        // apply everyhwere in the preprocessed source.) However, there are
        // still many who prefer writing ``using'' inside header files.
        //
        // Since we avoid ``using'', we directly use the ``fully qualified
        // name'' of the string class here, as ``std::string''.
        std::string log;
        std::string ownerName;        
        static int nextAccountNumber;
        // Same for map.
        static std::map<int, Account *> accounts;

    public:
        void deposit(float amount);
        bool withdraw(float amount);
        bool transferTo(Account &targetAccount, float amount);        
        void printDetails() const;        
        Account(std::string oName);        
        Account(std::string oName, float initialDeposit);        
        Account(const Account &) = delete;        
        Account & operator=(const Account &) = delete;        
        static Account * getAccount(int accountNumber);        
        ~Account();
};
