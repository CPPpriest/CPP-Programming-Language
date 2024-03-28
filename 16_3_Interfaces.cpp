#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <fstream>
using std::ofstream;

typedef unsigned char byte;

//---------INTERFACE--------------//
class IBinaryWriter //I for interface
{
    public:
        virtual void writeByte(byte b) = 0; // PURE VIRTUAL function
};

//---------IMPLEMENTATIONS--------------//
class ConsoleBinaryWriter : public IBinaryWriter
{
    public:
        void writeByte(byte b) override
        {
                cout << (b < 16 ? "0" : "") << std::hex << (int) b << " ";
        }
};

class FileBinaryWriter : public IBinaryWriter
{
    private:
        ofstream mFile;
    public:
        FileBinaryWriter(string fileName) : mFile(fileName){ }
        void writeByte(byte b) override
        {
            mFile.put(b);
        }
};

//-------------------------------------//


class Complex
{
    private:
        int mReal;
        int mImag;
    public:
        Complex(int r, int i): mReal(r),mImag(i) { }

        void write(IBinaryWriter *bw) const
        {
            //writes the values byte by byte

            for(int i=0; i < sizeof(mReal) ; ++i )
            {
                //byte x = ( (byte*) &mReal )[i];
                //convert int pointer to char pointer and use array notation
                bw->writeByte( ((byte*)(&mReal))[i] );
            }

            for(int i=0; i < sizeof(mImag) ; ++i )
            {
                bw->writeByte( ((byte*)(&mImag))[i] );
            }
        }
};



int main()
{
/*
    ConsoleBinaryWriter cbw;
    cbw.writeByte(0xAB);

    FileBinaryWriter fbw("test.txt");
    fbw.writeByte(0xAB);

    IBinaryWriter *bw1 = &cbw;
    bw1 -> writeByte(0xAB);

    IBinaryWriter *bw2 = &fbw;
    bw2 -> writeByte(0xC7);

    (&cbw) -> writeByte(0xAB); // writes byte to ostream via ConsoleBinaryWriter::writeByte
    (&fbw) -> writeByte(0xAB); // writes byte to file via FileBinaryWriter::writeByte
*/

    //--------------------------//
    /*
     * Realize that any definition that gets a IBinaryWriter Pointer
     * can write to a file or output stream without an extra definition
     *
     * send address of the destination stream to function and it can print
     * the values there without checking pointer type.
     *
     * assign pointer value:
     * to a FileWriter address -->> writes to file
     * to a ConsoleWrites address -->> writes to console
     * ...
     *
     */

    ConsoleBinaryWriter cbw;
    FileBinaryWriter fbw("test.txt");

    Complex cp(13,27);
    cp.write(&cbw);
    cp.write(&fbw);

    return 0;
}













