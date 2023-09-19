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

// *****************************
// *** BASIC INPUT/OUTPUT IN C++
// *****************************

#include <iostream> // Usually standard library headers
                    // have no .h suffix.

// Method 1 for accessing identifiers inside a namespace:
//     nspace::identifier
// Directly access the ``identifier'' inside ``nspace''.
// This is also known as the ``fully qualified name''.

// Method 2 for accessing identifiers inside a namespace:
//     using nspace::identifier;
// Makes upcoming references to ``identifier'' access ``nspace::identifier''.
// We are using this method to access the input/output objects in this file.

// Method 3 for using variables inside a namespace:
//     using namespace nspace;
// In practice, this is often used.
// Makes all upcoming references to *any* ``identifier'' in the ``nspace''
// access ``nspace::identifier''.

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    // Output to stdout.
    cout << "Hello world! 1\n" << "Hello world! 2\n";
    cout << 'H' << "ello world! " << 2 + 1 << "\n";
    cout << "Hello world! 4" << endl;

    // Input from stdin.
    cout << "Write the numbers you want to multiply: ";
    int x, y;
    cin >> x >> y;

    // The shift operators are left-associative and return the I/O stream back.
    // This allows for chaining the operator as in the examples above.
    // 
    //          [>>]                                   [>>]
    //          /  \                                   /  \
    //         /    \                                 /    \
    //      [>>]    [y]   == After reading x =>   [cin]    [y]
    //      /  \
    //     /    \
    // [cin]    [x]
    
    cout << x * y << endl;

    // Output to stderr.
    cerr << "Error!" << endl;

    return 0;
}
