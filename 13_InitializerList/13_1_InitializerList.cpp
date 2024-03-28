#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Account.h"

class Company
{
    public:
        enum Kind
        {
            Limited,        // 0
            Incorporated    // 1
        };
    private:
        string mName;
        Kind mKind;
        Account mAccount;
    public:
        //Member initializer list
        Company(string name,Kind kind) : mAccount(name) // mAccount(Account(name))
                                                        // or mAccount{Account(name)}
                                                        // or mAccount = Account(name)
        {
            mName = name;
            mKind = kind;
            // mAccount = account(name);    -->> Assignment operator(Not a copy construction)
            /* if there is no explicit call to constructor in member init list,
             * compiler implicitly calls default constructor of the member
             * so, all members must be initialized before the constructor body starts executing.
             */
       }

};


int main()
{
    //Company::Kind compKind = Company::Kind::Limited;

    return 0;
}
