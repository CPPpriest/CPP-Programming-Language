#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;



class Complex{
    private :
        float Real;
        float Imag;

    public:
        Complex()
        {
            Real = 0.f;
            Imag = 0.f;

            cout << "Complex() constructor" << endl;
        }

        Complex(float r)
        {
            Real = r;

            cout << "Complex(float) constructor" << endl;
        }

        Complex(float r, float i)
        {
            Real = r;
            Imag = i;

            cout << "Complex(float , float) constructor" << endl;
        }

        ~Complex()
        {
            cout << "~Complex" << endl;
        }

};



int main(){
    Complex* cpx = new Complex; // Allocates memory + calls constructor
                                // returns pointer
    delete cpx; // calls destructor + deallocates memory
                // takes pointer

    Complex* cpx1 = new Complex; // default construct
    delete cpx1;

    Complex* cpx2 = new Complex(5.f, 3.f); // parametrized construct
    delete cpx2;

    //memory allocation for array of objects
    Complex* cpxArray1 = new Complex[3];  // Allocate memory + call constructorS!
                                            // (calls constructors seperately for each obj in the array)

    delete[] cpxArray1;     // call destructorS + deallocate memory
                            // special delete[] syntax for obj array



    //obj array for parametrized objects
    Complex* cpxArray2 = new Complex[3]
    {
        {},         //-->> Complex()
        1.f,        //-->> Complex(float)
        {3.f, 5.f}  //-->> Complex(float, float)
    };

    delete[] cpxArray2;


    //Pointer array ( Array of 'pointer to Complex' )   -->> allocates memory for 3 pointers
    Complex **cpxPtrArray = new Complex*[3]{
        // initializing objects individually for each pointer in the array
        new Complex,
        new Complex(1.f),
        new Complex(2.f, 5.f)
    };

    //delete[] cpxPtr; -->> only frees the pointer array, NOT the objects that are pointed by them
    //-->> leads to memory leak

    for(int i=0; i<3; i++)
    {
        delete cpxPtrArray[i];
    }

    delete[] cpxPtr;

    return 0;
}










