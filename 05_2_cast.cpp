#include <iostream>

using std::cout;
using std::endl;


unsigned sum(unsigned i, unsigned j){
    return i+j;
}

double sum(double i, double j){
    return i+j;
}

int main(){

    unsigned char ch1= 1, ch2 = 3;
    //sum( ch1, ch2);
        //  Ambiguous call!
        //  sum can be both "sum_double_double" and "sum_unsigned_unsigned"

    sum((double)ch1, ch2);
    //  Forces compiler to use sum_double_double

    return 0;
}
/*
/home/priest/Documents/DataStructuresAlgorithms/main.cpp:18: error: call of overloaded ‘sum(unsigned char&, unsigned char&)’ is ambiguous
/home/priest/Documents/DataStructuresAlgorithms/main.cpp: In function ‘int main()’:
/home/priest/Documents/DataStructuresAlgorithms/main.cpp:18:8: error: call of overloaded ‘sum(unsigned char&, unsigned char&)’ is ambiguous
   18 |     sum( ch1, ch2);
      |     ~~~^~~~~~~~~~~
/home/priest/Documents/DataStructuresAlgorithms/main.cpp:7:10: note: candidate: ‘unsigned int sum(unsigned int, unsigned int)’
    7 | unsigned sum(unsigned i, unsigned j){
      |          ^~~
/home/priest/Documents/DataStructuresAlgorithms/main.cpp:11:8: note: candidate: ‘double sum(double, double)’
   11 | double sum(double i, double j){
      |        ^~~
*/
