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

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// We use the same Account class that we used in our previous examples, with
// the following changes:
//     - The instance and the static variable names have been prefixed with "m"
//       and "s" respectively.
//     - Initializer lists are used to initialize the instance fields.
//     - The fields mLog and mBalance have been moved under a ``protected''
//       access modifier.
#include "Account.h"

// The third fundamental mechanism of OOP is ``inheritance''. In essence,
// inheritance allows one to define new classes by ``extending'' other classes.
// The following code defines a ``PremiumAccount'' class that extends the
// Account class.
//
// This ``PremiumAccount'' class will contain an additional logic for deposit()
// function. When the deposit amount is larger than a particular threshold
// (specified during the construction), an additional 1.00 amount of money is
// deposited to the account by the bank as a reward.
//
// The fact that PremiumAccount extends Account implies that all fields and
// methods of Account (except the constructors) also exist in PremiumAccount.
// They are ``inherited''. In fact, if one defined the same constructors for
// PremiumAccount, PremiumAccount would effectively be the same type as
// Account.
//
// Inherited classes can be extended by defining extra fields and methods. It
// is also possible to ``sort of'' redefine the methods that exist in the
// inherited class.
//
// Interestingly, the jargon for inheritance is very rich. All of the following
// would be good descriptions for the code below. Please, make sure you know
// all of them:
//     - PremiumAccount ``inherits'' from Account.
//     - PremiumAccount ``derives'' from Account.
//     - PremiumAccount ``extends'' Account.
//     - PremiumAccount is a ``derived'' class of Account.
//     - PremiumAccount is a ``child'' class of Account.
//     - PremiumAccount is a ``subclass'' of Account.
//     - Account is a ``base'' class of PremiumAccount.
//     - Account is a ``parent'' class of PremiumAccount.
//     - Account is a ``super '' class of PremiumAccount.
//     - A PremiumAccount is an Account.
// The last sentence gives the perspective of an ``IS-A'' relationship between
// the two classes. When a child class C derives from a base class B, then we
// can logically say ``a C is a B'' because it carries all of the data and
// abstractions that B carries.
//
// The simplest way of declaring a child class is the syntax
//     class [ChildClass] : public [BaseClass]
// The keyword ``public'' concerns the accessibility of the inherited members.
// When public is used, the access restrictions of the inherited fields are
// preserved. We will not go into the detail what happens if you use a
// different access specifier. In practice, almost always ``public'' is used.
class PremiumAccount : public Account
{
    private:
        // Below is an additional member field that extends the Account class.
        //
        // Holds the threshold amount specified during the construction.
        float mThreshold;

    public:
        // In the case of simple single inheritance, the memory layout of the
        // child class consists of
        //     - An exact copy of the base class' memory layout, followed by
        //     - Additional fields defined by the child (in declaration order)
        // In other words, the base class is ``embedded'' in the child class
        // and forms a prefix of the child's memory layout. This implies that a
        // pointer to an instance of the child class is also a pointer to the
        // embedded base class instance. ***This is the reason that instance
        // functions of the base class keeps working on the child instance.***
        // (In more complicated forms of inheritance, the function calling
        // mechanism is a little different but we will not elaborate on it.)
        // 
        // In the constructor of a child class, one needs to specify how to
        // construct the ``embedded'' instance of the parent class. This is
        // done by triggering the parent class' constructor as part of the
        // initializer list. Additional fields defined by the child needs a
        // separate initialization of course.
        PremiumAccount(string ownerName, float threshold)
            : Account(ownerName), mThreshold(threshold)
        {
        }
        
        // [SIDE NOTE] For ease of expression, we used the term ``embedding''
        // to refer to the containment of the base class inside the child
        // class's memory layout. However, in some software engineering
        // contexts, this term may be synonymous with the term ``composition'',
        // which means containment as a member field WITHOUT inheritance.

        // One can use inheritance to extend a class with additional
        // abstractions by defining more functions.
        //
        // A getter for the mThreshold field.
        float getThreshold() const
        {
            return mThreshold;
        }

        // One can also ``sort of'' re-define existing abstractions. Below, we
        // re-define the deposit() function which already exists in the Account
        // class (and thus is inherited).
        //
        // However, in reality, the original function is NOT re-defined. It is
        // only hidden. The original deposit() function is actually a part of
        // the PremiumAccount class and can still be accessed as
        // Account::deposit().
        //
        // Such re-definition of a function from the base class is sometimes
        // casually called an ``override'', however, most programmers prefer to
        // use this exact term only for virtual functions (a concept that we
        // will see later.)
        //
        // Deposits the given amount of money into the account, triggering a
        // reward deposit if necessary.
        void deposit(float amount)
        {
            // Here, we call the member function deposit() inherited from
            // Account to perform a deposit.
            Account::deposit(amount);

            // The private fields of the base class are inaccessible to the
            // child. If the child class author wants to access any such
            // fields, the declaration of the base class has to be changed in
            // one of two ways:
            //     - Move the fields of concern under a ``protected'' access
            //       modifier. ``Protected'' fields are accessible to child
            //       classes but are private to any other code. In this
            //       example, we moved the fields mLog and mBalance under a
            //       ``protected'' access modifier in the Account class'
            //       declaration.
            //     - Include a ``friend declaration'' for the child class.
            //       Such a declaration would mean that the child class is a
            //       ``friend'' of the base class and therefore access its
            //       private fields. In our case, the friend declaration would
            //       look like:
            //           friend class PremiumAccount;
            //       Note that it is also possible to declare functions and
            //       non-child classes as friends.
            //
            // If the amount is sufficient, we also deposit a reward to the
            // account.
            if (amount >= mThreshold)
            {
                mBalance += 1.f;
                mLog += "reward(1.00)\n";
            }
        }
};

int main()
{
    Account alicesAccount("Alice");
    alicesAccount.deposit(10.f);
    alicesAccount.printDetails();

    PremiumAccount bobsAccount("Bob", 5.f);
    bobsAccount.deposit(10.f);
    bobsAccount.Account::deposit(10.f);
    bobsAccount.printDetails();

    return 0;
}
