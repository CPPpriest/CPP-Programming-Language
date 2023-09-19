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

// ***************************
// *** INTRODUCTION TO CLASSES
// ***************************

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;

#include <sstream>
using std::stringstream;
using std::ios_base;

#include <map>
using std::map;

// A helper function to convert floats into strings with two decimal digits.
// The code for this function is not important for this example.
string f2s(float f)
{
    stringstream ss;
    ss.precision(2);
    ss.setf(ios_base::fixed);
    ss << f;
    return ss.str();
}

// Most people consider that object-oriented programming (OOP) have four main
// mechanisms:
// 1. Abstraction
// 2. Encapsulation
// 3. Inheritance
// 4. Polymorphism
//
// In this file, we will see two of the mechanisms: abstraction and
// encapsulation. Abstraction and encapsulation usually go together.
// ``Abstraction'' involves the introduction of functions or ``methods'' that
// perform complicated tasks on data, thus hiding the complex details from the
// user. ``Encapsulation'' is the bundling of data with these methods, such that
// the access to the data is limited to what the abstraction provides.
//
// In C++, we usually represent abstracted/encapsulated data with classes.
// Technically speaking, it is also possible to use a structure for this
// purpose, as ``struct'' and ``class'' have only minor differences in C++.
// However, the psychological effects of the two keywords are different on
// programmers:
//     - A ``struct'' is usually used to define bare data, available to public
//       access and without any significant abstractions.
//     - A ``class'' usually represents data that is encapsulated and
//       significantly abstracted.
//
// Any variable (or entity) that carries the data defined by a class (such that
// its type is the class) is called an ``instance'' of that class. We also use
// the term ``object'' to refer to instances.

// The following class represents a bank account. A class itself is NOT an
// object, it defines a ``class'' of objects.  In particular, it describes the
// features (fields/methods) of the objects that fall under this particular
// class.
class Account
{
    // The following ``private'' label implies that what follows is only
    // accessible by the code written inside/for the class. Such labels in class
    // declarations are called ``access modifiers''. Here, we have a ``private''
    // access modifier.
    private:
        // Unless specified otherwise, all variables in a class are ``instance
        // variables'' or ``instance fields''. Such variables are tied to an
        // instance of the class. In general, each instance of the class lives
        // in a different memory location. Thus, each instance has its own
        // instance variables, which are independent from the others'.
        int accountNumber;
        float balance;
        string log;
        string ownerName;
        
        // The following variable/field is a ``static variable''/``static
        // field'' within the class as it is declared with the ``static''
        // keyword. Essentially, this variable is a global variable but it
        // resides under the class's namespace and it is subject to the access
        // rules defined by the access modifier it is under (in this case,
        // private). A static variable is singular, i.e., there is only one copy
        // of the variable and it is not part of any instance of the class.
        //
        // In C++, a static variable mentioned inside the class{} block acts as
        // a ``declaration'' only. One also needs to ``define'' the static
        // varible outside the class{} block, as you will see below. We will see
        // more about declarations/definitions when we study splitting the
        // classes into header-source pairs.
        //
        // Represents the next available account number. Since this is the
        // declaration, its initialization is done below, at the definition.
        static int nextAccountNumber;
        
        // Holds a mapping from the account numbers to actual Account instances.
        // Here, we use a class template from the standard library named
        // ``map'', which provides the functionality of a key-value store. The
        // first template parameter is the key type and the second parameter is
        // the value type.
        static map<int, Account *> accounts;

    // This ``public'' access modifier implies that what follows is accessible
    // by everyone. In most cases, the constructors and the methods that provide
    // abstractions go here.
    public:
        // Unless specified otherwise, all functions in a class are ``instance
        // functions'' or ``instance methods''. Such functions cannot be called
        // by themselves; you have to call them on a specific instance of the
        // class, like
        //     acct.deposit(4.0f);
        // where ``acct'' is an Account instance in this case. Instance methods
        // are logically bound to the instance that they are called on. Any
        // fields belonging to the instance can be accessed by directly
        // mentioning their name in the code.
        //
        // The following instance function is used to deposit money into an
        // Account.
        void deposit(float amount)
        {        
            balance += amount; // Recall a += b is the same as a = a + b.
            log += "deposit(" + f2s(amount) + ")\n";
        }
        
        // Another instance function similar to deposit(float), this time for
        // withdrawing money. The function returns false if the balance is
        // insufficient for such a withdrawal.
        bool withdraw(float amount)
        {
            if (balance >= amount)
            {
                balance -= amount;
                log += "withdraw(" + f2s(amount) + ")\n";
                
                return true;
            }
            else
            {
                return false;
            }
        }
        
        // This particular ``transferTo'' instance function transfers money from
        // this account to the given ``targetAccount''. Notice that the code for
        // this function CAN access the private fields of the parameter
        // targetAccount. This is due to that:
        //     - transferTo is a method of the Account class
        //     - targetAccount is an instance of the Account class
        // In other words, they belong to the same class and therefore no access
        // restrictions apply.
        bool transferTo(Account &targetAccount, float amount)
        {
            if (balance >= amount)
            {
                balance -= amount;
                targetAccount.balance += amount;
                
                log += "transferTo("
                       + to_string(targetAccount.accountNumber)
                       + ", "
                       + f2s(amount)
                       + ")\n";
                
                targetAccount.log += "transferFrom("
                                     + to_string(accountNumber)
                                     + ", "
                                     + f2s(amount)
                                     + ")\n";
                
                return true;
            }
            else
            {
                return false;
            }
        }
        
        // All instance functions, behind the curtain, have an extra invisible
        // parameter that is not declared. This parameter is a pointer that
        // points to the instance that the function is called on. For example,
        // the instance function
        //     void deposit(float);
        // in reality is a function like
        //     void deposit(Account*, float);
        // which takes two parameters. Consequently, the call
        //     acct.deposit(4.f)
        // actually translates to a call like
        //     deposit(&acct, 4.f).
        // C++ allows one to access this hidden pointer parameter via the
        // ``this'' keyword. In fact, one can use the ``this'' pointer to
        // perform any valid operation on the instance. For instance, one can
        // access the member fields/methods of an instance via ``this->''.  To
        // further exemplify, the code
        //     accountNumber
        // and the code
        //     this->accountNumber
        // are equivalent in the code below.        
        void printDetails()
        {
            cout << endl;
            cout << "**** ACCOUNT DETAILS ****" << endl;
            cout << "Account Memory Address: " << this << endl;
            cout << "Account Number: " << this->accountNumber << endl;
            cout << "Owner Name: " << this->ownerName << endl;
            cout << "Balance: " << f2s(this->balance) << endl;
            cout << "Transactions:" << endl;
            cout << this->log << endl;
            cout << endl;
        }
        
        // In OOP, class instances are initialized via ``constructors''. In
        // general, a class author is expected to write one or more constructors
        // that can ``construct'' instances of the class. If the author does not
        // write a constructor, then the compiler generates some ``implicit
        // constructors'' (or code that effectively act as them) on its own by
        // using a generic default logic.
        // 
        // [Side Note]: The implicit constructors, in particular, are
        //     - A default constructor, used for constructing instances without
        //       any parameters. This is removed once any constructor is written
        //       by the programmer.
        //     - A copy constructor, used for constructing instance that are a
        //       copy of another instance. This is removed once the programmer
        //       writes his/her own copy constructor.
        // We will see them in detail later.
        //
        // Constructors are the only way to create VALID instances of a class.
        // In general, a constructor is supposed to bring the new instance into
        // a ``consistent'' state upon creation. The constructor is the first
        // thing that is run on an instance after the memory is allocated for
        // the instance. No instance can be obtained without first constructing
        // it.
        //
        // In C++, constructors are implemented as instance functions that carry
        // the same name as the class. This is a language requirement: the name
        // is what the compiler checks to identify a constructor.
        //
        // The following constructor initializes the ``Account'' object (that is
        // being constructed) by setting its
        //     - balance to 0,
        //     - log to "",
        //     - accountNumber to next available account number,
        //     - ownerName to the provided parameter.
        // Notice that the code is accesses and modifies the static (and thus
        // singular) variable ``nextAccountNumber''.
        Account(string oName)
        {
            log = "";
            balance = 0.0f;
            accountNumber = nextAccountNumber;
            ownerName = oName;
            
            // Add the account to the map.
            accounts[accountNumber] = this;
            
            // Increment the next available account number.
            nextAccountNumber++;
            
            cout << ownerName << "'s account is constructed." << endl;
        }
        
        // Since constructors are functions, they can be overloaded. This gives
        // the user of the class a choice for initialization for the new
        // instance. The following overload offers the user to put an initial
        // amount of money into an Account while opening (constructing) it.
        Account(string oName, float initialDeposit)
        {
            log = "initialDeposit(" + f2s(initialDeposit) + ")\n";
            balance = initialDeposit;
            accountNumber = nextAccountNumber;
            ownerName = oName;
            
            // Add the account to the map.
            accounts[accountNumber] = this;
            
            // Increment the next available account number.
            nextAccountNumber++;
            
            cout << ownerName
                 << "'s account is constructed with initial balance "
                 << f2s(initialDeposit)
                 << "."
                 << endl;
        }
               
        // In C++, all new classes normally come with an ``implicit copy
        // constructor'' written by the compiler. This constructor allows one to
        // copy an instance into another one by simply copying its fields. For
        // objects representing entities that cannot be copied (as in this
        // case), it is better to delete the copy constructor. The following
        // code does it. We will cover this constructor in detail later.
        Account(const Account &) = delete;
        
        // Similary, the compiler also creates an implicit assignment operator
        // implementation, which assigns an instance into another one by copying
        // its fields. For our case, this operator should also be disabled.
        Account & operator=(const Account &) = delete;
        
        // Classes can also contain ``static functions''/``static methods'' that
        // are called without being tied to any instance, just like a regular
        // function. The following is a static method that returns the Account
        // instance identified by the accountNumber, by querying our static
        // map<>. It is supposed to be called with the class namespace, as
        // Account::getAccount().
        static Account * getAccount(int accountNumber)
        {
            return accounts[accountNumber];
            // Returns ``nullptr'' (the null pointer) if the account number is
            // missing. This is because the default value for pointers is
            // ``nullptr''.
        }
        
        // When the reference to an object is programmatically lost, its memory
        // is deallocated by the compiler. However, individual memory clean-up
        // might not be sufficient for some objects. In our case, the loss of an
        // Account logically translates to ``closing'' it and we need to remove
        // the Account from the static map<> Account::accounts.
        //
        // C++ gives a way to perform additional clean-up logic via
        // ``desctructors''. A ``destructor'' is an instance function carrying
        // the name of the class with a preceding ``tilde''. It takes no
        // parameters because the call to the destructor is often done
        // implicitly by the compiler upon loss of the object.
        //
        // The destructor is run by the compiler just before the memory
        // deallocation. After the destructor finishes, the destroyed object is
        // logically perished and should not be accessed.
        //
        // At runtime, there are three main situations that trigger the
        // ``destruction'' of an object O:
        //     - Reaching the end of a scope that contains O as a defined
        //       variable or parameter.
        //     - Finishing the evaluation of an expression/statement that
        //       contains O as a temporary object.
        //     - The ``delete'' keyword. (We will study this later.)
        //
        // The following is the destructor for the Account class.  It removes
        // the account from the static map<> by using the account number.
        ~Account()
        {               
            accounts.erase(accountNumber);
            
            cout << ownerName << "'s account is destroyed." << endl;
        }
};

// The following are the ``definitions'' of the static variables that match the
// ``declarations'' inside the Account class. Note that we do not need to use
// the keyword ``static'' as they are already declared as static in the class.
int Account::nextAccountNumber = 1;
map<int, Account *> Account::accounts; // No need to initialize the map, its
                                       // default constructor already creates an
                                       // empty map.

int main()
{
    Account alicesAccount("Alice");
    Account bobsAccount("Bob", 5);
    
    alicesAccount.deposit(9);
    alicesAccount.transferTo(bobsAccount, 3);
    bobsAccount.withdraw(7);

    alicesAccount.printDetails();
    Account::getAccount(2)->printDetails(); // Get's a pointer to Bob's account.
    
    Account("Temporary").printDetails();
    // The temporary account is destroyed at this point.
    
    {
        Account charliesAccount("Charlie");
        charliesAccount.printDetails();
        cout << "Address of account with account number 4: "
             << Account::getAccount(4)
             << endl;
        // charliesAccount destroyed at this point.
    }
    
    // This line prints 0, because Account::getAccount(4) returns ``nullptr''.
    // In modern C++, we use ``nullptr'' for null pointers. Do not use NULL,
    // unless you are conforming to a style already present in the codebase.
    cout << "Address of account with account number 4: "
         << Account::getAccount(4)
         << endl;
    
    return 0;
    // The alicesAccount and bobsAccount are destroyed at this point.
}
