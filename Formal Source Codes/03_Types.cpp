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

// ********************
// *** NEW TYPES IN C++
// ********************

#include <iostream> // Contains code similar to:
                    //     namespace std
                    //     {
                    //         ...
                    //         ... cout ...
                    //         ...
                    //         ... endl ...
                    //         ...
                    //     }

#include <string>   // Contains code similar to:
                    //     namespace std
                    //     {
                    //         ...
                    //         ... string ...
                    //         ...
                    //         ... wstring ...
                    //         ...
                    //     }

// From <iostream>.
using std::cout;
using std::endl;

// From <string>.
using std::string;
using std::wstring;

int main(int argc, char **argv)
{
    // Old C types:
    // int, short, long, unsigned, char, float, double, void.

    // New type in C++: bool.
    // Great for passing/returning Boolean flags, such as:
    //     printProgram(..., bool isIndented);
    // Also comes with two new keywords ``true'' and ``false''.
    // Consumes 1 byte.
    bool b1 = true; // 1
    bool b2 = false; // 0

    bool b3 = 4; // Casts as true.
    bool b4 = -3; // Casts as true.
    bool b5 = 0; // Casts as false.

    cout << b1 << ' ' << b2 << ' ' << b3 << ' ' << b4  << ' ' << b5 << endl;

    // New type in C++: wchar_t.
    wchar_t wc = L'C'; // Roughly the same as ``char'' but consumes 4 bytes and
                       // represents a wide-character. (Might be 2 bytes for
                       // other compilers). Useful for international strings.
                       // Literals prepended with ``L''.

    // New type in C++: string.
    // This is not really a language type but a type that comes from the
    // standard library. Preferred over char* in C++ for representing strings.
    string s1 = "This is a string.";
    string s2 = "Another string.";

    // Appending strings are possible with ``+''.
    string s = s1 + " " + s2;

    cout << s << endl;

    // New type in C++: wstring.
    // Roughly the same as ``string'' but for wchar_t.
    wstring ws = L"This is a wide string.";

    return 0;
}
