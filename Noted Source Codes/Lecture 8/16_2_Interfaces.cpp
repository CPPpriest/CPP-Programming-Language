#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <fstream>
using std::ofstream;

typedef unsigned char byte;

//interface: a class with NO fiels and containing only purely virtual functions (roughly).
//a vtable entry.

//---------INTERFACE--------------//
class IBinaryWriter //I for interface
{
    public:
        virtual void writeByte(byte b) = 0; // PURE VIRTUAL function
        //must be initialized to 0 (syntax)
};

//---------IMPLEMENTATIONS--------------//
class ConsoleBinaryWriter : public IBinaryWriter
{
    public:
        void writeByte(byte b) override
        {
                cout << (b < 16 ? "0" : "") << std::hex << (int) b << " "; // if b<16, add "0" in the beginning
        }
};

class FileBinaryWriter : public IBinaryWriter
{
    private:
        ofstream mFile;
    public:
        FileBinaryWriter(string fileName) : mFile(fileName) //file is opened with construction
        {

        }

        void writeByte(byte b) override
        {
            mFile.put(b);   // put(char) method of ostream object
        }

        //~FileBinaryWriter(){} //implicit destructor
        //file is closed when during destruction
};



int main()
{
    ConsoleBinaryWriter cbw;
    //byte b = '0xAB';
    cbw.writeByte(0xAB);

    FileBinaryWriter fbw("test.txt");
    fbw.writeByte(0xAB);


    /* a pointer to base the class can be assigned to any derived class
     * thanks to virtual (late binding), it will call the appopriate method.
     *
     * So, a single pointer type can be used to call various implementations:
     *
     * Polymorphism achieved.
    */


    IBinaryWriter *bw1 = &cbw;
    bw1 -> writeByte(0xAB);

    //bw1 = &fbw;   //also works
    IBinaryWriter *bw2 = &fbw;
    bw2 -> writeByte(0xC7);


    // or simply
    (&cbw) -> writeByte(0xAB); // writes byte to ostream via ConsoleBinaryWriter::writeByte
    (&fbw) -> writeByte(0xAB); // writes byte to file via FileBinaryWriter::writeByte


    return 0;
}













