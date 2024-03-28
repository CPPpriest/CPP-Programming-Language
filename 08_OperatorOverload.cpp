
#include <iostream>

using std::cout;
using std::endl;

struct Complex{
    float real;
    float imag;
};


//Complex multiplier(const Complex &a,const Complex &b)
Complex operator*(const Complex &a,const Complex &b)
{
    //a.real = 1;   //---> error: assignment of member ‘Complex::real’ in read-only object

    Complex ans = { a.real*b.real - a.imag * b.imag ,
                    a.real*b.real - a.imag * b.imag     };
    return ans;
}

std::ostream& operator<<(std::ostream &out , Complex &c )
{
    cout << c.real << "+(" << c.imag << ")i" << endl;

    /*  operator<< here is a member of ostream obj. cout
     *  not complex &c
     *  it is NOT a RECURSION ! */

    return out;
}


int main() {
    Complex a = {12,2}; // 12 + 2i
    Complex b = {3,9};  //  3 + 9i
    Complex c;

    // for assignment op. -->> operator*() must return a complex type
    //assignment is defined for struct by default as shallow copy

    c = a * b;
    // operator*() -->> it works as a function
    // it takes both a and b as parameter (Unlike member operators)

    cout << c;
    // operator<<(cout, c);

    return 0;
}







