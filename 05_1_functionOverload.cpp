#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;



//---Function Overloading
//  The name of the function is overloaded with multiple implementations
//  (Not Overriding)!!!



//Compiler gets the "Effective Name" of the function
//it is determined with function name and parameter types


//effective name: swap_int*_int*
void swap(int* x, int* y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


//effective name: swap_float*_float*
void swap(float* x, float* y)
{
    float temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


//effective name: swap_std::string*_std::string*    //-->> compiler uses the fully qualified name.
void swap(string* x, string* y)
{
    string temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


int sum(int i, int j)
{
    return i+j;
}


int main()
{
    int x = 3, y = 5;   //swap_int*_int*
    swap(&x, &y);

    float a = 3.f, b = 5.f; //swap_float*_float*
    swap(&a, &b);

    //Compiler may do an implicit cast (when a function with given parameter types not available)
    char ch1= 1, ch2 = 3;
    cout << sum(ch1, ch2) << endl;


    return 0;
}

// in C, identically named functions -> name clash !!!
// C++ is context-independent: Return type of the fuunction is not part of the effective name
// since functions are determined via parameter types and not the context !!!
//(which type should be returned in the context)




