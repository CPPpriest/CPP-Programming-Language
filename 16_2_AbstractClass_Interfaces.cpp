#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

#include <fstream>
using std::ofstream;


typedef unsigned char byte;

//Redundant logic: Logic that is redundantly repeated.
//Specialization by Inheritance



//----------Interface------------//
class IBinaryWriter
{
    public:
        virtual void writeByte(byte b) = 0;
        virtual ~IBinaryWriter() {};
};


class BinaryWriterBase : public IBinaryWriter
{
    private:
        unsigned mBytesWritten;

    protected:
        virtual void writeByteToDestination(byte b) = 0;
        //this is not an interface function,
        //not supposed to be called by instances.(only child classes can access/call)

    public:
        virtual void writeByte(byte b) override final // final :function cannot be overriden (by derived classes)
        {
            mBytesWritten++;
            writeByteToDestination(b);
        }
        //now, any derived class can override writeByteToDestination
        //and writeByte method will implement their code + increment the no. of written bytes
};


//----------Implementations------------//
class ConsoleBinaryWriter : public BinaryWriterBase
{
    public:
        void writeByteToDestination(byte b) override final
        {
                cout << (b < 16 ? "0" : "") << std::hex << (int) b << " ";
        }

        virtual ~ConsoleBinaryWriter() override { }
};

class FileBinaryWriter : public BinaryWriterBase
{
    private:
        ofstream mFile;
    public:
        FileBinaryWriter(string fileName) : mFile(fileName){ }
        void writeByteToDestination(byte b) override final
        {
            mFile.put(b);
        }

        virtual ~FileBinaryWriter() override { }
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
            for(int i=0; (size_t) i < sizeof(mReal) ; ++i ){
                bw->writeByte( ((byte*)(&mReal))[i] );  }

            for(int i=0; (size_t) i < sizeof(mImag) ; ++i ){
                bw->writeByte( ((byte*)(&mImag))[i] );  }
        }
};



int main()
{
    return 0;
}
