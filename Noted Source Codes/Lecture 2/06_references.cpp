#include <iostream>

using std::cout;
using std::endl;

struct Player{
    char name[32];
    float passing;
    float tackling;
    float shooting;
};

// in C: type is "struct Player" -->> in C++, "Player" can be used as type name as well !

//Copy whole struct -->> waste of memory and cpu
float totalByValue(Player p){
    cout << &p << endl;
    return p.passing + p.tackling + p.shooting;
}

//dereferencing needed -->> extra operations/symbols
float totalByPointer(Player* p){
    cout << p << endl;
    return p->passing + p->tackling + p->shooting;
}

//References to the same object
float totalByRef(Player& p){
    cout << &p << endl;
    return p.passing + p.tackling + p.shooting;
}


int main() {
    Player p = {"Player's name", 7.4, 8.1, 3.5};

    totalByValue(p);
    totalByPointer(&p); //"address of" operator

    totalByRef(p);  //address value is automatically sent to function
    // Expectation: reference should be to an l_value (May have exceptions)

    return 0;
}


/*

output:
0x7ffe7d115bd0
0x7ffe7d115c00
0x7ffe7d115c00

Since first one is passByValue, its address is different
*/

