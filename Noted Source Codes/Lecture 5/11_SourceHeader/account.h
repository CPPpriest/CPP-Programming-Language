#pragma once

#include <string>
//using std::string;

#include<map>
//using std::map;

//using statements are also included to source file
//may result in name clashes in large projects
//instead, use them in source file and use fully qualified name in header file ! 



//Contains the prototypes

class Account
{
private:
    int accountNumber;
    float balance;
    std::string ownerName;	//Fully qualified name: std::string
    std::string log;	

    static std::map<int, Account*> accounts;	// Static member DECLERATION

public:
    Account(int acctNum, float initialBalance, std::string owner);
    
    ~Account();

    Account(const Account &other)=delete;
    Account& operator=(const Account &other)=delete;

    void deposit(float amount );

    bool withdraw(float amount );
 

    bool transferTo(Account &target, float amount);

    void printLog();

    void printDetails();

    static Account * getAddress(int acctNum);	

};
