#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;

int main()
{
    //Old C types: int, short, long, float, double, unsigned, void

    //New type: bool
    bool a = true;  //1
    bool b = false; //0

    //bool is 1 bit storage
    //integers casted automatically to bool values:
    //0 is false, any non-zero value is true

    bool c1 = 5;    //non-zero
    bool c2 = -9;   //non-zero
    bool c3 = 3.2;  //non-zero
    bool c4 = 0;    //0 value for int type
    bool c5 = 0.0;  //0 value for float type

    cout << c1 << c2 << c3 << c4 << c5 << endl;


    //New type: wchar_t     -->> wide char
    // 2 or 4 bytes depending on compiler
    //represent chars doesnt fit ASCII table

    wchar_t wc = L'ö';
    cout << wc << endl;

    //string type
    string str1 = "First str";
    string str2 = "Second str";



    return 0;
}
