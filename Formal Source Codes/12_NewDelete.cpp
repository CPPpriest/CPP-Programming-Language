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

// **************************************
// *** DYNAMIC MEMORY ALLOCATION WITH NEW
// **************************************

#include <iostream>
using std::cout;
using std::endl;

// A trimmed-down implementation of Complex suitable for our needs in this
// example.
class Complex
{
    public:
        float real;
        float imag;

    public:
        Complex()
        {
            real = 0.f;
            imag = 0.f;

            cout << "Complex() called." << endl;
        }

        Complex(float r)
        {
            real = r;
            imag = 0.f;

            cout << "Complex(float) called." << endl;
        }

        Complex(float r, float i)
        {
            real = r;
            imag = i;

            cout << "Complex(float, float) called." << endl;
        }

        ~Complex()
        {
            cout << "~Complex" << endl;
        }
};

int main()
{
    // Objects constructed as variables or temporary values have limited
    // lifetimes and they do not live beyond the function call that they are
    // used in. If one wants to create objects whose lifetime extend beyond the
    // function call (and this is often the case in large projects), ``dynamic
    // memory allocation'' should be used. C++ offers the ``new'' keyword to
    // create ``dynamic'' objects at runtime. In essence, the keyword does the
    // following:
    //     - Allocates the necessary dynamic memory for the new object or the
    //       new array of objects.
    //     - Calls the specified constructor(s) on the on the allocated memory.
    // Notice that ``new'' guarantees that a constructor is executed. This
    // helps to ensure that all objects in the program are properly
    // constructed.
    //
    // Similar to malloc() of C, ``new'' returns a pointer, whose base type is
    // the class of the constructed object(s). The pointer's value is the
    // address of the new object or the address of the first object in the
    // array if an array is allocated.
    //
    // When ``dynamic'' objects are no longer needed, one should dispose them
    // via the ``delete'' keyword. In essence, this keyword
    //     - Calls the destructor on the object(s).
    //     - Deallocates the memory of the object(s).
    // Notice that the keyword forces destruction before deallocation, helping
    // to maintain the proper construction-destruction cycle of objects in the
    // program.
    //
    // The parameter to the ``delete'' keyword should be the pointer to the
    // object or the pointer the first element of the array that requires
    // deallocation. The base type of the pointer is used to determine the
    // destructor to be called. It is therefore important to maintain a correct
    // base type in an pointer before passing it to delete.
    //
    // [IMPORTANT] One important notion that needs care is that when arrays are
    // to be decallocated with ``delete'' one needs to write ``[]'' after the
    // keyword, so that the compiler is aware that the destructor is to be
    // called on all elements in the array. Please see the examples below.
    //
    // What follows below is some example code that shows how one can create
    // various dynamic Complex instances with ``new'' and how these instances
    // should deallocated with ``delete''.

    // A single instance constructed with the default constructor.
    Complex *cpx1 = new Complex;
    delete cpx1;

    cout << endl;

    // A single instance constructed with a parameterized constructor.
    Complex *cpx2 = new Complex(1.f, 2.f);
    delete cpx2;

    cout << endl;

    // An array of instances constructed with the default constructor.
    // The instances in the array are adjacent in memory.
    Complex *cpxArray1 = new Complex[3];
    // Recall the pointer arithmetic - array notation relation from C:
    // One can now access the three elements as cpxArray1[0], cpxArray1[1] and
    // cpxArray1[2].
    delete [] cpxArray1;

    cout << endl;

    // An array of instances constructed with different constructors.
    Complex *cpxArray2 = new Complex[3]
    {
        {}, // default
        3.f, // parameterized
        {4.f, 5.f} // parameterized
    };
    delete [] cpxArray2;

    cout << endl;

    // A set of instances constructed with different constructors, together
    // with a pointer array whose elements point to the constructed instances.
    // The instances are not necessarily adjacent in memory in this case. (Of
    // course, their pointers are.)
    Complex **cpxPtrArray = new Complex*[3]
    {
        new Complex,
        new Complex(1.f),
        new Complex(2.f, 3.f)
    };
    // One can now access the objects as *cpxPtrArray[...].
    for(int i = 0; i < 3; i++)
    {
        delete cpxPtrArray[i];
    }
    delete [] cpxPtrArray;

    // Normally, all objects allocated with ``new'' should be ``deleted''
    // before their pointer is thrown away (programmatically). If the the
    // pointer to a dynamic object is lost before it is deleted, then the
    // object will live and occupy memory until program termination. Losing
    // memory due to such lost objects is called a ``memory leak''. Memory
    // leaks are one of the most common bugs among C++ programs. There are some
    // helper mechanisms (such as smart pointers) offered by C++ to avoid
    // leaks. Unfortunately, these are beyond the scope of this course.
    //
    // Memory leaks are usually the result of ``forgetting'' to delete dynamic
    // objects whose references are about to be lost. The following is a good
    // example of that.
    double **dblPtrArray = new double*[3];
    for (int i = 0; i < 3; i++)
    {
        dblPtrArray[i] = new double((double)i);
    }
    // ...
    // Do some useful work with your dynamic doubles.
    // ...
    delete [] dblPtrArray;
    // Oops, we just ``leaked'' three doubles.

    // Typically, you can say that your program is leaking if its memory
    // consumption is steadily increasing (without any reasonable cause) as the
    // program keeps running. However, there are more concrete analyzers
    // available. A useful tool to detect memory leaks is ``valgrind''. I
    // suggest running ``valgrind ./12_NewDelete'' to detect the leak in this
    // code.
    return 0;
}



