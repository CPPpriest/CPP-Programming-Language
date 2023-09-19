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

// ****************************
// *** MEMBER INITIALIZER LISTS
// ****************************

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// We use the same Account class that we used in our last example. No need to
// look into the details of the header file below in this project.
#include "Account.h"

// A class that represents a company. Each company has a name, a kind (limited
// or incorporated) and a bank account.
class Company
{
    public:
        // In addition to member fields and functions, one can also write types
        // inside classes. To be more precise, it is possible to declare/define
        //     - enums
        //     - classes/structs
        //     - typedefs
        // inside a class. The access modifiers also apply to types: A private
        // type would only be accessible within the class, whereas a public
        // type would be accessible overall.
        //
        // Similar to members, the class name acts like a namespace for the
        // types defined inside a class. When these types are mentioned
        // outside, one needs to use the fully qualified name.
        //
        // The following is the declaration of a public enum, which logically
        // corresponds to a company kind (limited or incorporated). Inside the
        // class, Kind can be used to refer to this enum. Outside the class,
        // Company::Kind needs to be used.
        //
        // The enum also acts like a namespace. In this example, the values
        // defined under the enum can be accessed outside the class as:
        //     Company::Kind::Limited  and  Company:Kind::Incorporated
        //
        // To be backward compatible with C, where enum values are globally
        // available, the values can also be accessed without mentioning the
        // enum name. The following are also valid for accessing the enum
        // values, but not suggested:
        //     Company::Limited  and  Company::Incorporated
        enum Kind
        {
            Limited,
            Incorporated
        };

    private:
        // For complicated classes, it is a good practice to prefix the
        // instance variable names with some fixed string, so that they are
        // easily distinguised in the code. "_", "m_" and "m" are some of the
        // commonly used prefixes. In this code, we will use "m" as the prefix
        // for our instance variables. Similar prefixes are also used for other
        // types variables. For instance, some programmers prefix static
        // variables with "s".
        //
        // It is good practice to use ``const'' for member variables whose
        // value will be fixed throughout the lifetime of the object. Below we
        // have two such variables.
        //
        // The name of the company.
        const string mName;
        // The kind of the company.
        const Kind mKind;
        // The bank account of the company.
        Account mAccount;

    public:
        // When the body of a constructor starts running, all instance fields
        // have already been constructed (with their default constructors
        // unless specified otherwise). In other words, what looks like
        // initializing instance fields in the body of a constructor is
        // actually a re-assignment and NOT a construction.
        //
        // This is not a problem for primitive types such as int, because the
        // default constructor does little (or no) work. However, for
        // complicated classes, the default constructor may have done a lot of
        // work that will be thrown away by the re-assignment.
        //
        // C++ offers a syntax to call constructors of the member fields before
        // the constructor body starts running. The syntax requires the
        // programmer to put a : after the constructor prototype and then list
        // the members with their construction parameters. The list is often
        // called the ``member initializer list''.
        //
        // Any instance members missing from the list would be constructed with
        // their default constructor. If a member has no default constructor
        // then it should be listed in the initializer list. Interestingly, the
        // order of the members in the list has no significance. The members
        // are initialized in the order they appear in the class declaration.
        // One should pay attention to this fact if the construction of one
        // member uses another member as a parameter (or as a dependency).
        //
        // Notice that ``const'' member variables can only be initialized with
        // the initializer list. Assignment to a const variable is not possible
        // within the constructor body.
        //
        // In general, one should use initializer lists to initialize member
        // fields.
        Company(string name, Kind kind) : mName(name),
                                          mKind(kind),
                                          mAccount(name)
        {
            cout << mName << " is constructed." << endl;
        }

        // An alternative to initializing the member fields with an initializer
        // list is to call a different constructor. This is especially done if
        // the class has multiple constructors and a portion of the logic in
        // the constructors are the same, i.e., ``redundant''. Calling
        // constructors from other constructors is known as ``constructor
        // chaining'' or ``constructor delegation''. Note that when constructor
        // chaining is performed, the body of the called constructor executes
        // before the body of the caller constructor.
        //
        // The following constructor for the Company class allows the user to
        // construct a Company by only providing the company name; and the
        // company kind defaults to Limited. This constructor simply ``chains''
        // the other constructor by providing a kind=Limited parameter.
        //
        // Notice that there are two alternatives to this code:
        //     1. Use a default parameter kind = Limited on the first
        //        constructor. In that case, one cannot add specialized
        //        behavior, such as the warning written below.
        //     2. Use an initializer list. In that case, the initialization of
        //        the mName and mAccount fields is ``redundant'' logic and thus
        //        the code would be longer and more difficult to maintain.
        // To sum up, constructor chaining gives the simplest code in this
        // case.
        Company(string name) : Company(name, Kind::Limited)
        {
            cout << "Warning: Kind was unspecified. Defaulting to Limited." << endl;
        }

        // In the case of constructors, first the member fields are constructed
        // and then the class itself. Actually, it would be more accurate to
        // say the class's construction starts with the construction of its
        // member fields.
        //
        // In the case of destructors, it is the other way around. The class's
        // destruction ends with the destruction of its members. In other
        // words, the body of a destructor runs before the members are
        // destroyed, and thus all members are still valid at destruction time.
        //
        // When you run this code, you will see that the company destruction
        // messages appear before the account destruction messages.
        ~Company()
        {
            cout << mName << " is destroyed." << endl;
        }
};

int main()
{
    Company cargoCompany("Cargo Company");

    Company candyCompany("Candy Company",
                         Company::Kind::Incorporated);

    return 0;
}
