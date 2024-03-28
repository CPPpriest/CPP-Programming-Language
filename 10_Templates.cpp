#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

template<typename T>
class Complex{
    private :
        T mReal; //m , m_ , _m, etc.. for "member"
        T mImag;
    public:
        Complex()   // 1.Default Constructor
        {
            mReal = (T) 0;
            mImag = (T) 0;

            /* T typed identifier = int literal
             * int 0 casted to (T) type, then T type is assigned
             * Which is ambiguous to operator= in most cases.
             * -->> Complex can be used only with castable types:char, int, flaot...
             */

            cout << "Complex() constructor" << endl;
        }

        Complex(T r) // 2.Parametrized Constructor
        {
            mReal = r;
            mImag = (T) 0;

            cout << "Complex(T) constructor" << endl;
        }
        Complex(T r, T i) // 2.Parametrized Constructor
        {
            mReal = r;
            mImag = i;

            cout << "Complex(T , T) constructor" << endl;
        }

        Complex(const Complex & c) // 3.Copy Constructor

        //const: c object will not be modified
        //&: avoid infinite recursion (it is mandatory!)
        {
            mReal = c.mReal;
            mImag = c.mImag;

            cout << "Complex(const Complex&) constructor" << endl;
        }
        //Note: not right way to define copy construct


        //Assignment Operator
        Complex<T> operator=(const Complex<T> & c)
        {
            mReal = c.mReal;
            mImag = c.mImag;

            cout << c.mReal << " +i" << c.mImag << " is assigned to " << this->mReal << " +i" << this->mImag << endl;
            return *this;
        }
        //Usually, the type that is referred to (the calling instance's type) is returned.
        //It is done via '*this'.(Returning the instance itself)

        Complex<T> operator*(const Complex<T> &c )
        {
            return Complex<T>(  mReal * c.mReal - mImag * c.mImag,
                                mReal * c.mImag + mImag * c.mReal   );
        }

        friend std::ostream & operator<<(std::ostream &out, const Complex<T> &c);//friend function decleration/prototype


        //setter and getter functions
        T getReal() const{  //function does not modify instance members
            return mReal;
        }
        T getImag() const{
            return mImag;
        }

        void setReal(T r){
            mReal = r;
        }

        void setImag(T i){
            mImag = i;
        }

        /*"Property"
         *
         * a data member that have a -> getter method said to have "read property"
         *                           -> setter method said to have "write property"
         *
         * "Property" is a "logic field". meaning it is an abstract concept!
         * a setter/getter may modify more than one data filed.
         * This does not change the property of a particular data member
         *
         */
};

//friend function definition    -->> friend methods can access private members
template<typename T>
std::ostream & operator<<(std::ostream &out, const Complex<T> &c)
{
    out << c.mReal << "+(" << c.mImag << "i)";
    return out;
}



int main(){
    Complex<float> c1;
    Complex<float>();//Complex() ,without an identifier, called like this

    Complex<float> c2(2.f,3.f);
    Complex<float>(2.f,3.f);

    Complex<float> c3(2.f);
    Complex<float>(2.f);

    //Other ways to call the constructor
    Complex<float> c4 = 1.f; // with assignment operator
    (Complex<float>) 1.f; // with type cast

    //Copy Constructor
    Complex<float> c5(c4);
    Complex<float> c6 = c4;


    Complex<float> c7;
    c7 = c6; // c7.operator=(c6); instance operator
    // assigns c6 member values to c7 and returns c7.

    //Since it returns the same type ==>> it can be chained!
    c7 = c6 = c5;


    Complex c9 = {"Real", "Imag"};
    // Complex<const char*>
    // not called a function that will trigger the compiler to instantiate that method and return an error
    // until a function is called (such as sum), it will compile without an error!

    return 0;
}










