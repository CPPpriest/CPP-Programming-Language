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

// ``Polymorphism'' is the 4th main mechanism of OOP and often accompanies
// inheritance. It is the notion of having multiple different implementations
// that can be accessed through a single interface. In C++, this is usually
// achieved with ``virtual'' functions/methods as we describe below.

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// We use the same Account and PremiumAccount classes that we used in our last
// example, with the following changes:
// - The deposit() function in Account is now is declared as a ``virtual''
//   function.
// - The deposit() function in PremiumAccount includes an ``override''
//   specifier.
#include "Account.h"
#include "PremiumAccount.h"

// Suppose the imaginary government in this example wants to make a stimulus
// payment of 10.00 to all accounts. We will do it by accessing all accounts
// via the static getAccount() function with the account numbers. To keep the
// example simple, we assume that there are always only two accounts with
// account numbers 1 and 2.
void payStimulus()
{
    for(int i = 1; i <= 2; i++)
    {
        // getAccount() returns an Account pointer. Since we have two classes
        // Account and PremiumAccount (and all PremiumAccounts are also
        // Accounts), the pointer may point to an instance of either type. To
        // keep consistent with our classes' logic, we want to call:
        //     - Account::deposit on Account instances, and
        //     - PremiumAccount:deposit on PremiumAccount instances.
        //       (So that a reward is deposit as part of this transaction.)
        //
        // Normally, the compiler uses the pointer base type to determine which
        // function to call. In the code below, the pointer's base type is
        // Account, and therefore the compiler attempts to call
        // Account::deposit, regardless of whether the pointed instance is an
        // Account or a PremiumAccount.
        //
        // To call PremiumAccount::deposit, we need to convert the pointer type
        // to PremiumAccount*. While this can be done with a C-style cast, it
        // only makes sense to do it after we make sure that the pointed
        // instance is really a PremiumAccount. Unfortunately, we do not have a
        // mechanism that can tell that. We could probably implement such a
        // mechanism, but that would be additional work (and even more work if
        // we want to make it generic so that new child classes can easily
        // become part of the mechanism.)
        //
        // Luckily, C++ can implicitly identify the type of the instance and
        // call the right function for us, if we specify the need for it. This
        // is achieved by declaring the function of concern to be ``virtual''.
        // In this example, we declared Account::deposit as a ``virtual
        // function''/``virtual method'' by using the ``virtual'' keyword
        // before its declaration in the Account class. In particular, we have
        // the following line in Account's declaration:
        // 
        //     virtual void deposit(float amount);
        //
        // When one or more functions are declared as ``virtual'' in a class C,
        // this creates a hidden member field in C. This member occupies the
        // beginning of the memory layout of C and is a pointer to a data
        // structure known as the ``virtual function table'' or shortly the
        // ``vtable'' of C. Each virtual function is assigned a logical index
        // in this table. The table is then essentially a mapping from the
        // virtual function indices to the addresses of the function
        // implementations. Going forwards, we will refer to this hidden field
        // as the ``vtable'' field.
        //
        // The compiler implicitly initializes the ``vtable'' field as part of
        // the constructor, and sets it to point to the virtual function table
        // of the class being constructed. This means, even if we do casts to
        // to change the pointer base type, vtable field still points the
        // vtable of the original type that underwent construction.
        //
        // When we call a virtual method f() on a pointer (or reference) of
        // base type C, the ``vtable'' is used to figure out which
        // implementation to call. As we have said before, for a C* c, the call
        //     c->f(...);
        // would normally translate to a call like
        //     f(c, ...);
        // However, if f() is known to be a virtual function of C, then this
        // code translates to
        //     c->vtable[F](c, ...);
        // where F is the virtual function index of f() in C's vtable.
        //
        // [NOTE] The exact vtable mechanism is actually more complicated.
        //        This is because C++ have more complicated forms of
        //        inheritance such as multiple and virtual inheritance. The
        //        description above, however, would work well for a simple
        //        single inheritance scenario like in this example.
        Account *acctPtr = Account::getAccount(i);
        acctPtr->deposit(10.f); // Calls the right function since deposit() is virtual.

        // When a child class C changes the behavior of a virtual function f()
        // by providing a new implementation, we say that the new
        // implementation ``overrides'' the original implementation of f().
        // Alternatively, we can say that f() is ``overridden'' in C.  The new
        // implementation is called an ``override''.
        // 
        // Let us also mention that the use of the virtual keyword is optional
        // for an overriding function. For instance, the deposit() function
        // automatically becomes a virtual function of PremiumAccount, even if
        // it is not declared as virtual. This implies that any child class of
        // PremiumAccount can further override the deposit function.
        // 
        // Simply implementing a virtual function in a child class is
        // sufficient to have an override. However, it is advised to mark such
        // functions with the ``override'' specifier. In particular, the
        // declaration of PremiumAccount class contains the following
        // declaration of deposit():
        // 
        //     void deposit(float amount) override;
        //
        // The specifier triggers a compile-time check of ensuring that the
        // function deposit() was indeed a virtual function of the base class.
    }
}

int main()
{
    Account alicesAccount("Alice");
    PremiumAccount bobsAccount("Bob", 5.f);

    payStimulus();

    alicesAccount.printDetails();
    bobsAccount.printDetails();

    return 0;
}
