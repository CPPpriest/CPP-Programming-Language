#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;


typedef unsigned char byte; // "byte" is used for "unsigned char"

//interface(for C++): a class with virtual functions that are not implemented.

//---------INTERFACE--------------//
class IBinaryWriter //I for interface
{
    public:
        virtual void writeByte(byte b) = 0; // PURE VIRTUAL function
};
//IBinaryWriter instance is just a pointer to virtual fınction table (8 bytes)



//---------IMPLEMENTATIONS--------------//
//a class derived from interface is called an implementation of the interface.
class ConsoleBinaryWriter : public IBinaryWriter
{
    public:
        void writeByte(byte b) override
        {
                //cout << std::hex << (int) b << " "; //writes b in hex form
                cout << (b < 16 ? "0" : "") << std::hex << (int) b << " "; // if b<16, add "0" in the beginning
        }
};



int main()
{
    ConsoleBinaryWriter cbw;
    byte b = 0xA4; //164
    cbw.writeByte(b);

    return 0;
}
