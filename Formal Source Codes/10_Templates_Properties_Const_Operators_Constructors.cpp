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

// *************************************************************************************
// *** CLASS TEMPLATES, PROPERTIES, CONSTRUCTORS,
// *** OPERATOR OVERLOADING IN CLASSES, CONST
// *************************************************************************************

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <string>
using std::string;

// The following is a class template representing a complex number. The type
// parameter T acts as the underlying type of the number's components so that
// the user can select a type with sufficient precision.
template<typename T>
class Complex
{
    // In this particular implementation of Complex, we want to prevent the
    // modification to the instance fields by outsiders. Therefore, we declare
    // the fields under a private access modifier. However, private fields
    // cannot be read, either.  Therefore, the read access to these fields is
    // given by the public ``getter'' functions below.
    private:
        T real;
        T imag;

    public:
        // Instance functions that read and return fields are called
        // ``getters''. The following function is a getter for the ``real''
        // field.
        //
        // The function is marked as ``const'' (stands for constant) because it
        // does not make any modifications to the instance's data. In general,
        // one should label all modification-free instance methods with const.
        // This has the following benefits:
        //     - Prevents you from accidentally modifying data.
        //     - Clarifies to the caller that the function does not modify data.
        //     - Tells the compiler that the method is modification-free. This
        //       is important, as one can call only ``const'' methods on
        //       ``const'' objects.
        T getReal() const
        {
            return real;
        }

        // The getter for the ``imag'' field.
        T getImag() const
        {
            return imag;
        }

        // It is also possible to define `setters' that set fields. The
        // following functions, if they were defined, would be setters for the
        // real and imag fields. Since we want readonly access to the fields, we
        // are not going to define these setters this time.
        //
        // void setReal(T r)
        // {
        //     real = r;
        // }
        //
        // void setImag(T r)
        // {
        //     imag = r;
        // }
        //
        // One can, of course, use const and/or & in the parameter for a setter.
        // For instance, the following would also be a valid setter prototype:
        //
        // void setReal(const T &r);

        // Defining a setter instead of allowing direct access may have the
        // following benefits:
        //     - Enables one to perform checks during the set operation.
        //     - Enables one to have side effects as part of the set operation.
        //     - The behavior of the setter function can be changed later,
        //       without the need to recompile the sources that use the setter.
        //     - Setters can be part of interfaces (a concept that we will see
        //       later).
        //     - In OOP, most programmers have a reluctance to modify fields
        //       directly.  Setters, therefore, encourage modification to the
        //       fields.

        // Data exposed via getters and/or setters are often referred as
        // ``properties''. To be more precise, the term ``property'' refers to
        // the imaginary entity represented by the get/set methods rather than
        // its actual ``backing'' field in the class. In fact, it is possible
        // that a property's value is formed by multiple backing fields in a
        // class. Similarly, a backing field may contribute to multiple
        // properties. One should be also be aware that getting or setting a
        // property may actually involve side effects other than simply
        // accessing/changing the backing fields.

        // There are four fundamental constructor types in C++:
        // 1. Default constructor
        // 2. Parameterized constructors
        // 3. Copy constructor
        // 4. Move constructor
        // The code below shows the types 1, 2, and 3. We will skip type 4 as it
        // is a somewhat recent addition to the language and involves detailed
        // concepts such as r-value references which is outside the scope of
        // our examples.

        // Interestingly, the compiler may use constructors in a variety of
        // scenarios to cover up missing functionality. For instance, the
        // compiler may use a parameterized constructor to perform a cast, in
        // the absence of an explicitly implemented cast logic. Whether this
        // cover-up behavior of the compiler is beneficial is subject to debate.
        // On the plus side, it helps with backward compatibility and reducing
        // the developer workload. On the minus side, it may add functionality
        // to the classes without the developer noticing, with potentially
        // unwanted consequences.

        // Type 1
        // A parameterless constructor is called the ``default constructor''.
        // It is triggered when:
        //     - A variable is defined without any parameters.
        //     - The constructor is directly invoked without any parameters to
        //       create a temporary object (or a dynamically allocated object as
        //       we will see later).
        //
        // If the class author does not define any constructors, then a default
        // constructor is ``implicitly'' defined by the compiler. This implicit
        // constructor does not do any initialization (according to the
        // standard), in which case the member values are garbage.
        //
        // The following default constructor creates a zero complex. Notice that
        // the type T has to support cast from 0 for the instantiated code to
        // compile.
        Complex()
        {
            real = (T) 0;
            imag = (T) 0;

            cout << "Default constructor called." << endl;
        }

        // Type 2
        // A constructor is ``parameterized'' if it accepts one or more
        // parameters. These constructors are invoked when:
        //     - A variable is defined with the parameters.
        //     - The constructor is directly invoked with the parameters.
        //     - A variable is initialized with a value that can be cast to the
        //       parameter type of the constructor.
        //     - A value of the parameter type is cast to the class, unless
        //       there is an explicitly implemented cast operator.
        //
        // The following parameterized constructor creates a Complex from a T by
        // assigning it as the real value and leaving the imaginary part as zero.
        Complex(T r)
        {
            real = r;
            imag = (T) 0;

            cout << "Parameterized constructor (T) called. " << endl;
        }

        // The following parameterized constructor creates a Complex directly
        // from the given parameters.
        Complex(T r, T i)
        {
            real = r;
            imag = i;

            cout << "Parameterized constructor (T, T) called." << endl;
        }

        // Type 3
        // A constructor that takes a reference an object of the same class is
        // called a copy constructor. The reference may be a const reference or
        // not. Usually, a const reference is preferred.
        //
        // The purpose of the copy constructor is to create a logical ``copy''
        // of the object. Ideally, this copy becomes an object that is
        // independent from the original object. The copy constructor is invoked
        // when:
        //     - A variable is defined with a parameter of the same class.
        //     - A variable is initialized with a value of the same class.
        //     - The constructor is directly invoked with a parameter of the
        //       same class.
        //
        // If the class author does not define any copy constructors, then a
        // copy constructor is implicitly defined by the compiler. This implicit
        // constructor simply does a field-by-field copy.
        Complex(const Complex<T> &c)
        {
            real = c.real;
            imag = c.imag;

            cout << "Copy constructor called." << endl;
        }

        // Type 4
        // A ``move constructor'' is similar to a copy constructor with the
        // exception that it ``moves'' data from the original object to the
        // constructed object, instead of copying it. The ownership of the data
        // switches to the constructed object and the original object becomes
        // unusable (roughly speaking). As mentioned before, we will not study
        // move constructors.

        // Operator overloading can also be done via instance methods in a
        // class. When an operator is overloaded as an instance method, the left
        // operand acts as the ``this'' instance logically tied to the method.
        // Notice that overloading operators inside classes allow operator to
        // access the private members of the class.
        //
        // The following method is an overload of the * operator for Complex.
        Complex<T> operator*(const Complex<T> &c)
        {
            return Complex<T>(real * c.real - imag * c.imag,
                              real * c.imag + imag * c.real);
        }

        // One of the operators that can be overloaded is the assignment
        // operator =. It is invoked when:
        //     - An already constructed object is assigned a new value via =.
        //
        // Traditionally, an assignment operator is supposed to return the
        // reference to the left operand, by returning ``*this''. This allows
        // one to chain the assignment operator as:
        //     a = b = c;
        //
        // Since the = operator does an assignment to already constructed
        // objects, one may need to implement a ``clean-up logic'' in this
        // operator for complicated classes. This is a fundamental difference
        // between the assignment operator and the copy constructor. The copy
        // constructor initializes an object that is ``being constructed'' for
        // the first time, so no clean-up logic is necessary.
        Complex & operator=(const Complex<T> &c)
        {
            real = c.real;
            imag = c.imag;

            cout << "Assignment operator called." << endl;

            return *this;
        }
};

// The following definition overloads the << operator so that we can write
// Complex objects to output streams. Since the the Complex<T> is a template,
// this function also has to be defined as a template. Notice that we cannot put
// this method into the Complex class because the left operand is not Complex.
template<typename T>
ostream & operator<<(ostream &out, const Complex<T> &c)
{
    out << c.getReal() << "+(" << c.getImag() << "i)";

    // [Side Note]: If the Complex type did not have any getters, then
    // the code for this operator could not access the real and the imaginary
    // parts of Complex, since they are private. If such an access is desired,
    // however, one can enable by declaring this operator/function as a
    // ``friend'' of Complex, by writing the following in the Complex class:
    //
    //     friend ostream & operator<<(ostream &, const Complex<T> &);

    return out;
}

int main()
{
    Complex<float> c1;   // Calls the default constructor.
    Complex<float>();    // Calls the default constructor. This code creates a
                         // temporary value rather than a variable.
    
    // The following cannot be used to call the default constructor as it is
    // instead evaluated as function declaration by the compiler:
    //     Complex<float> c();
    
    cout << endl;

    // When using template parameters, there are many times one can avoid them
    // and let the compiler guess it.

    Complex<float> c2(1.f, 1.f);    // Calls the parameterized constructor (T, T).
    Complex<float> c3 = {1.f, 1.f}; // Calls the parameterized constructor (T, T).
    Complex<float>(1.f, 1.f);       // Calls the parameterized constructor (T, T).
    
    // There are many cases where one can omit the template parameters when
    // referring to class templates so that the compiler can guess it. Below, we
    // are declaring a Complex<float>, as the compiler guesses the type from the
    // constructor parameters.
    Complex c4(1.f, 1.f);

    cout << endl;

    Complex<float> c5(1.f);  // Calls the parameterized constructor (T).
    Complex<float> c6 = 1.f; // Calls the parameterized constructor (T).
    (Complex<float>) 1.f;    // Calls the parameterized constructor (T).
    (Complex<float>) 1;      // Calls the parameterized constructor (T).

    cout << endl;

    Complex<float> c7(c6);  // Calls the copy constructor.
    Complex<float> c8 = c7; // Calls the copy constructor.

    cout << endl;

    c8 = c7;      // Calls the assignment operator. (c8.operator=(c7)) 
    c1 = c2 = c3; // Calls the assignment operator, first for c2 = c3,
                  // then for c1 = ... .

    cout << endl;

    cout << c8; // Calls the << operator. (operator<<(cout, c8))

    cout << endl;

    // Exercise: Why does the following code compile?
    //           What statement can you add to it to get a compilation error
    //           regarding the Complex<string> type?
    Complex<string> stringComplex("[RealPart]", "[ImagPart]");
    cout << stringComplex << endl;

    cout << endl;

    return 0;
}
