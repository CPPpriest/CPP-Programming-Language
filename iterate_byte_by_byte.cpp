#include <iostream>
using std::cout;
using std::endl;


int main()
{
    int var = 10;

    char* p = (char*) &var;

    cout << (int)*(p) << endl;      //00001010  ->  10
    cout << (int)*(p+1) << endl;    //00000000  ->  0
    cout << (int)*(p+2) << endl;    //00000000  ->  0
    cout << (int)*(p+3) << endl;    //00000000  ->  0

    cout << (int)*(p+4) << endl;    //rand memory  ->  random Value

    return 0;
}
