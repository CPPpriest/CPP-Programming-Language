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
// *** FUNCTION TEMPLATES IN C++
// *****************************

#include <iostream>
using std::cout;
using std::endl;

// A specific function that swaps two floats.
void swap(float &x, float &y)
{
    float temp = x;
    x = y;
    y = temp;
}

// A generic function that swaps two values belonging to same type T. The code
// for this function is not yet compiled, we do not yet know what T is. The code
// is generated and compiled when the template is ``instantiated'' with a
// particular type assigned to T.
template<typename T>
void swap(T &x, T &y)
{
    T temp = x;
    x = y;
    y = temp;
}

// It is possible to have more than one parameter for a template. For instance,
// the code below defines a generic function that can take parameters of two
// different types T1 and T2.
template<typename T1, typename T2>
void f(T1 a, T2 b)
{
    // Do nothing... Only here to exemplify.
}

int main(int argc, char **argv)
{
    // This code does not instantiate any templates, as there is already a
    // swap(float&, float&) function.
    float x = 1.1f, y = 2.2f;
    swap(x, y);
    
    // This code instantiates the swap<T>(T&, T&) template, by setting T = int.
    // The code for the instantiated template is completed and compiled at this
    // point.
    int a, b;
    swap(a, b);
    
    // This code also instantiates the template, this time by explicitly setting
    // T = int. However, since such an instantiation is already compiled, the
    // call will simply call the previously-compiled instantiation rather than
    // creating a new one. Explicity instantiations like this one are not
    // frequently used for function templates.
    swap<int>(a, b); 
    
    // This code instantiates the swap<T>(T&, T&) template by setting T = float,
    // (rather than using the already available swap(float& float&)) because we
    // explicitly asked the compiler to instantiate the template. The code for
    // the instantiated template is completed and compiled at this point. It is
    // possible for two functions swap(float&, float&) and swap<T=float>(T&, T&)
    // to co-exist, because they get different names behind the curtain.
    swap<float>(x, y);
    
    return 0;
}
