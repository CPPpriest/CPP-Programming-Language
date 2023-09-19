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

// ******************
// *** C++ REFERENCES
// ******************

#include <iostream>

using std::cout;
using std::endl;

// This is a somewhat large structure.
// In general, it is a good idea to avoid copying
// this structure to save time and memory.
struct Player
{
    char name[32];
    float shooting;
    float passing;
    float tackling;
    //...
};

// In C, all parameters are passed by value. When a function like the below is
// called, the passed-in parameter will be copied to callee's function frame.
// This might be very inefficient if the parameters are large.  Also, any
// modifications done to the copy will not be retained after the function
// returns.
float totalByValue(Player p)
{
    cout << "The address of parameter p in totalByValue() is "
         << &p << "." << endl;

    return p.shooting + p.passing + p.tackling; //...
}

// To avoid such copying, we can instead ask for a pointer as the parameter.
// Technically speaking, the pointer is still copied by value, but since it is a
// much smaller object (8 bytes in 64-bit programs), the efficiency impact is
// much less. Also, since the (copied) pointer is still pointing to the original
// object, any modifications to the object would be retained.
float totalByPointer(Player *p)
{
    cout << "The value of the pointer parameter p in totalByPointer() is "
         << p << "." << endl;
    
    // Recall p->field is the same as (*p).field.
    return p->shooting + p->passing + p->tackling; //...
}

// However, the pointer implementation (arguably) has some drawbacks:
//   - It reveals the fact that the object of question is large and thus copies
//     should be avoided.
//   - It forces the caller to know and use pointers.
// C++ introduces ``references'', which are essentially abstraction of pointers
// with the following (arguable) benefits:
//   - Their syntax do not reveal the pointer detail. They look like you are
//     passing/accessing the object of question directly.
//   - You may force the caller to pass a parameter ``by reference'' without
//     the caller knowing it.
//   - Their usage is somewhat limited compared to pointers, which helps
//     programmers avoid bugs and enables compilers for more optimizations. For
//     instance, a reference cannot be modified (i.e., its pointer cannot be
//     modified.)
// In the function prototype below, the & sign is NOT the reference/address-of
// operator. It is the ``reference type''.
float totalByReference(Player &p)
{
    // The & sign below IS the reference/address-of operator.
    cout << "The address of parameter p in totalByReference() is "
         << &p << "." << endl;
    
    return p.shooting + p.passing + p.tackling; //...
}

int main(int argc, char **argv)
{
    Player p = {"Player One", 3.0f, 4.0f, 2.0f};
    
    cout << "The address of variable p in main() is "
         << &p << "." << endl;
    
    totalByValue(p);
    totalByPointer(&p);
    totalByReference(p);
    
    return 0;
}
