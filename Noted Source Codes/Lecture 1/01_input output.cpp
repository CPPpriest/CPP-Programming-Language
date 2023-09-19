#include <iostream>

// Standard library headers have NO SUFFIX
//it is possible to use C headers(with .h suffix) in C++


int main()
{
    std::cout << "Hello World!\n";
    //shift operator here is overloaded.

    std::cout << "first line\n" << "second line\n";
    //operator << can be chained.

    std::cout << 1+2 << std::endl;
    // an expression like 1+2 is used.
    // be careful with precision of the operation

    int x,y;
    std::cin >> x >> y;
    //reads 2 integers from input stream, writes on x and y
    //Works as a left associative tree structure
    std::cout << x*y << std::endl;

    std::cerr << "ERROR!" << std::endl;
    //standard error stream



    return 0;
}
