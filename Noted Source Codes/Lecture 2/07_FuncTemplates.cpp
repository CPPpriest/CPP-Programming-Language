#include <iostream>

using std::cout;
using std::endl;

#define SWAP(x,y)
//  resolved as text at preprocessor time (have some issues)
//  templates resolved at compile time

//  template is not a function
//  functions and classes are instantiated from the template at compile time


template <typename T>
void swap(T& a, T& b){  //---GENERIC
    T temp = a;
    a = b;
    b = temp;
    cout << "GENERIC swap" << endl;
}

void swap(float& a, float& b){  //---FLOAT
    float temp = a;
    a = b;
    b = temp;
    cout << "FLOAT swap" << endl;
}


//multiple template parameters
//(multiple parameters can be given to a template)
template <typename T1, typename T2>
T1 operation(T1 t1, T2 t2)
{
    return t1 + t2;
}
// T1 must support operator+(T2) that returns T1




int main() {

    int a,b;
    char m,n;

    swap(a,b);
    swap(m,n);


    // When float type is defined, this function is directly called.
    // Not the generic one

    float x,y;
    swap(x,y);  // (FLOAT)
    swap(a,b);  // (GENERIC)


    //  for float, generic function is instantiated as:
    swap<float>(x,y);
    //explicitly instantiating by providing the type


    //swap(a,x);
    /*  Error ---> parameters must be of the same type.
     *  There is no template fitting this. So no template instantiation.
     *  no function generated --> no match/no auto type cast
     */


    // multpile template parameters
    cout << operation(15,'k') << endl;

    return 0;
}

/*
 *  output:
 *      GENERIC swap
 *      GENERIC swap
 *      FLOAT swap
 *      GENERIC swap
 *      GENERIC swap
 *      122
 *
 */




