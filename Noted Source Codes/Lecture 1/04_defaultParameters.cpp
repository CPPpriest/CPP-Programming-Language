#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;


//  1. Default-value parameters should be the last.
//  2. The user can only provide the parameters in the order they are defined.

// Order is important:
//  Regularly changing parameters -> comes first
//  Rarely changing parameters -> at last


void printFloatValue(float f, unsigned indentation = 0) //indentation param. default value is 0
{
    for(unsigned i=0; i < indentation; ++i)
        cout << ' ';

    cout << f << endl;
}

float transform(float x, float scale = 1.f, float translate = 0.f)
{
    return x * scale + translate;
}

int main()
{
    printFloatValue(3.14f, 4);
    printFloatValue(3.14f);     //  ==>> printFloatValue(3.14f, 0);


    cout << transform(2.f) << endl;
    cout << transform(2.f, 3.f) << endl;
    cout << transform(2.f, 3.f, 4.f) << endl;

    // transform(2.f , , 4.f);   INVALID!


    return 0;
}
