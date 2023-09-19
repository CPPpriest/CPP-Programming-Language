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
// *** OPERATOR OVERLOADING IN C++
// *******************************

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

// A struct that represents a complex number.
struct Complex
{
    float real;
    float imag;
};

// In C++, an operator [OP] is logically represented by a function named
// operator[OP]. For binary operators, an expression like
//     x [OP] y
// is equivalent to calling
//     operator[OP](x, y)
// Then, just like functions, most operators can be overloaded with custom
// implementations for different parameter types. In fact, most operators are
// ``already'' overloaded since they already work for different types.

// An implementation of * operator for complex types. We use a ``&'' in the
// parameters to avoid unnecessary copying.  We also use ``const'' so that
// compiler prevents us from modifying the parameters by mistake.
// [Side Note] Recall from C that:
// - ``Complex * const'' is a const pointer to a Complex,
// - ``Complex const *'' is a pointer to a const Complex,
// - ``const Complex *'' is also a pointer to a const Complex,
// - ``Complex const * const'' is a const pointer to a const Complex,
// - ``const Complex * const'' is also a const pointer to a const Complex.
// With the same logic, ``const Complex &'' or ``Complex const &'' is a
// reference to const Complex. One does not need to make the reference itself
// const. References in C++ act as const pointers; they cannot be modified to
// point to a different object.
Complex operator*(const Complex &a, const Complex &b)
{
    Complex c = { a.real * b.real - a.imag * b.imag,
                  a.real * b.imag + b.real * a.imag};
    return c;
}

// An implementation of << operator for the ostream and complex pair. We use a
// ``&'' for the ostream parameter to avoid copying the output stream. We return
// the same reference back so that one can continue chaining << operators to
// this output stream.
ostream & operator<<(ostream &out, const Complex &c)
{
    out << c.real << "+(" << c.imag << "i)";
    
    return out;
}

int main(int argc, char **argv)
{
    Complex a = {2, 1}; // 2 + 1i
    Complex b = {3, 2}; // 3 + 2i
    
    // Calls operator*(const Complex &, const Complex &).
    Complex c = a * b;
    
    int x = 4, y= 5;
    
    // This one calls the original integer multiplication.
    int z = x * y;
    
    // Uses operator<<(ostream &, const Complex &).
    cout << "a * b = " << c << "." << endl;

    // Notice how the expression above is evaluated.
    // The precedence of the << operator is to the left.
    // The following is the expression tree.
    // Each << call returns ``cout'' so that each subsequent << call
    // is carried out against ``cout'' as the first parameter.
    //
    //                     <<
    //                      *
    //                 ***********
    //                 *         *
    //                <<        endl
    //                 *
    //             *********
    //             *       *
    //            <<      "."
    //             *
    //          *******
    //          *     *
    //         <<     c
    //          *
    //     ***********
    //     *         *
    //    cout  "a * b = "
    //
    
    return 0;
}
