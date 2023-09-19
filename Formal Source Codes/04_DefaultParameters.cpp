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

// ***********************************
// *** DEFAULT-VALUE PARAMETERS IN C++
// ***********************************

#include <iostream>
using std::cout;
using std::endl;

// Default-value parameters should be the last parameters in a function
// declaration. The following is not a valid prototype for a function:
//     void printFloatValue(unsigned amountOfIndentation = 0, float f);
// This is particularly required because C++ does not provide a way to skip a
// parameter in the middle while calling a function.

// The function below has a default-value of 0 for its second parameter.
void printFloatValue(float f, unsigned amountOfIndentation = 0)
{
    for (unsigned i = 0; i < amountOfIndentation; i++)
    {
        cout << ' ';
    }

    cout << f << endl;
}

// Another function that takes two default-value parameters.
float transformCoordinate(float x,
                          float scaleAmount = 1,
                          float translationAmount = 0)
{
    return scaleAmount * x + translationAmount;
}

int main(int argc, char **argv)
{
    printFloatValue(3.14f, 0);

    // The call below effectively calls printFloatValue(3.14f, 0). The
    // missing parameter is completed with the default-value
    // mentioned in the declaration of the function.
    printFloatValue(3.14f);

    printFloatValue(3.14f, 4);

    
    cout << transformCoordinate(3) << endl;
    // Effectively calls transformCoordinate(3, 1, 0).

    cout << transformCoordinate(3, 2) << endl;
    // Effectively calls transformCoordinate(3, 2, 0).

    cout << transformCoordinate(3, 2, 4) << endl;
    // Effectively calls transformCoordinate(3, 2, 4).
    
    // As mentiond before, one cannot skip from the middle. The following code,
    // for instance, is not valid:
    //     transformCoordinate(3, ,4);

    return 0;
}
