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
    /*
        Company(string name,Kind kind) : mName(name), mKind(kind) , mAccount(name)
        {
            cout << "Company(string, Kind) is called." << endl;
        }

        Company(string name) : mName(name), mKind(Kind::Limited) , mAccount(name)
        {
            cout << "Warning: Kind is default to Limited";
        }
    */

        Company(string name,Kind kind) : mName(name), mKind(kind) , mAccount(name)
        {
            cout << "Company(string, Kind) is called." << endl;
        }

        // Constructors of a class can CALL EACH OTHER in member init list !!!
        Company(string name) : Company(name, Kind::Limited)
        {
            cout << "Warning: Kind is default to Limited";
        }

        // 1.Desturctor function runs.
        // 2.Members are destructed (By individual destructor calls in the body)
        // 3.Memory is deallocated.

        ~Company()
        {

        }

};


int main()
{
    Company a("TAI");

    return 0;
}

/*
 * TAI's account is constructed.
 * Company(string, Kind) is called.
 * Warning: Kind is default to LimitedTAI's account is destroyed.
 *
 */




