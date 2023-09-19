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
        // 1.Memory is allocated.
        // 2.Memory is initialized (member initialization list).
        // 3.The constructor function run.

        Company(string name,Kind kind = Kind::Limited) : mAccount(name), mName(name), mKind(kind) {}

            // { mName = name;}       -->> mName is as well, already constructed before the execution body
                                    //-->> then, assigned to a different value inside
                                    //-->> it can as well be initialized in the member init. list
};


int main()
{
    //Company::Kind compKind = Company::Kind::Limited;

    return 0;
}
