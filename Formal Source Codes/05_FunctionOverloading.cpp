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

// *******************************
// *** FUNCTION OVERLOADING IN C++
// *******************************

// In C++, like many other object-oriented languages, one can define multiple
// functions with the same name but with different parameter types. Such a
// function (or its name) is said to be ``overloaded''. Overloading
// implementations of a function, despite having the same name, can be called
// individually by providing parameters with the matching types. Behind the
// scenes, the compiler incorporates the parameter types into the function name
// while producing the object code and therefore is able to compile separate
// implementations for the overloaded function.

// Pay attention to that ``overloading'' is NOT ``overriding'', a concept that
// we will see later.

#include <iostream>
using std::cout;
using std::endl;

// Effective name of the function (roughly): swap_int*_int*
void swap(int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

// Effective name of the function (roughly): swap_float*_float*
void swap(float *x, float *y)
{
    float temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

// Function ``swap'' is *overloaded* with two implementations.

int main(int argc, char **argv)
{
    int x = 3, y = 5;
    swap(&x, &y); // Calls swap(int*, int*).

    float xf = 3.3, yf = 5.5;
    swap(&xf, &yf); // Calls swap(float*, float*).

    // Function overload greatly simplifies the function names by avoiding
    // specialization. For instance, one can write a generic write() function
    // for multiple types as:
    //     write(7);
    //     write(3.14f);
    //     write("Hello");
    // Without overloading, these would have to be
    //     writeInt(7);
    //     writeFloat(3.14f);
    //     writeString("Hello");
    
    // When in doubt, one can explicitly select a particular overloading of a
    // function by applying a type cast to the parameters. As in:
    //     write((float)3.14);

    return 0;
}
