#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;

int main()
{
    //primitive types, by default, support << overloaded operator fo standard io (cout,cin...)
    //string type also supports standard IO

    //initialized with const char[], const char*
    string str1;
    str1 = "Hello world\n";
    cout << str1;

    const char* name = "Hesoyam\n";
    str1 =  name;
    cout << str1;


    //---------Operations---------//

    string s1 = "hello", s2="world";

    //---concatenation
    string s3 = s1 + s2;
    cout << s3 << endl;

    //---length
    cout << s3.length() << endl;
    cout << s3.size() << endl;

    //string is a defined type in standard library and nothing like C char arrays.
    cout << string("helloworld").size() << endl;
    //same as the above: 10
    //on the other hand, const char array is actually made up of 11 elements ('\0' at the end)


    //---Indexing
    cout << s3[8] << endl;

    //---Substrings
    string statement = "I am 23 years old.";
    string age = statement.substr(5,2);     //from index 5, take first 2 chars
    cout << age << endl;


    //---Comparison
    bool b0 = (s1 == s3);   // "hello" == "helloworld"
    bool b1 = (s1 != s3);   // "hello" != "helloworld"
    bool b2 = (s1 <= s3);   // "hello" <= "helloworld"  // s1 comes before s3 lexicographically
    bool b3 = (s1 >= s3);   // "hello" >= "helloworld"  // s1 comes after s3 lexicographically

    cout << b0 << endl;
    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;


    //---Searching
    string st00 = "helloworld";
    string st01 = "lowo";

    cout << st00.find(st01) << endl;    //returns the index where st01 starts


    return 0;
}
