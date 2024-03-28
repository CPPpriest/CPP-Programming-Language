#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <fstream>
using std::ofstream;



typedef unsigned char byte;



//writes binary data to a stream
class IBinaryWriter
{
    public:
        virtual void writeByte(byte b) = 0;
        //virtual ~IBinaryWriter() = 0; //pure virtual destructor
        virtual ~IBinaryWriter() {}; //empty implemented virtual destructor

        //if purely virtual is declared, all derived classes must implement their own
        //this way, derived ones define their implicit destructors
};

class ConsoleBinaryWriter : public IBinaryWriter
{
    public:
        void writeByte(byte b) override
        {
                cout << (b < 16 ? "0" : "") << std::hex << (int) b << " ";
        }

        virtual ~ConsoleBinaryWriter() override { }
};

//define a simple class to see its destructer is called by FileBinaryWriter destructor
//and not IBinaryWriter destructor



class destructable
{
    public:
        ~destructable()
        {
            cout <<  "destructable obj is destructed." << endl;
        }
};


class FileBinaryWriter : public IBinaryWriter
{
    private:
        ofstream mFile;
        destructable mDest;
    public:
        FileBinaryWriter(string fileName) : mFile(fileName){ }
        void writeByte(byte b) override
        {
            mFile.put(b);
        }

        virtual ~FileBinaryWriter() override { }
        //even though it doesnt have the same name as base destructor,
        //it is an override.
};


class Complex
{
    private:
        int mReal;
        int mImag;
    public:
        Complex(int r, int i): mReal(r),mImag(i) { }

        void write(IBinaryWriter *bw) const
        {
            for(int i=0; i < sizeof(mReal) ; ++i ){
                bw->writeByte( ((byte*)(&mReal))[i] );  }

            for(int i=0; i < sizeof(mImag) ; ++i ){
                bw->writeByte( ((byte*)(&mImag))[i] );  }
        }
};



int main()
{

    //ConsoleBinaryWriter* cbw = new ConsoleBinaryWriter();
    FileBinaryWriter* fbw = new FileBinaryWriter("test.txt");

    //cbw -> writeByte(0xAF);
    //fbw -> writeByte(0xAF);

    IBinaryWriter *bw = fbw;

    bw -> writeByte(0xCD);

    //cbw has an allocated memory
    //delete bw;    //-->>delete calls the destructor of bw which is an IBinaryWriter
    //so it calls the destructor of IBinaryWriter
    //which does not deallocate the memory.
    //SO -->> declare a virtual or empty destructor in the interface.

    delete bw;
    //output: destructable obj is destructed.

    //if destructor in IBinaryWriter wasnt defined,
    //there would be no output + memory leak
    //(since file binary destructor is not called, memory is not freed)

    return 0;
}













