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


//specialization by inheritance
//define an extra class that inherits from IBinaryWriter
//yet adds extra common feature that are used by implementations

//adding an extra feature to interface,
//since it is also an abstract class, it cannot be instantiated
//so, implementations must derive from this class (if requires the feature)
class BinaryWriterBase : public IBinaryWriter
{
    private:
        unsigned mBytesWritten;  //numb. of bytes written
    public:
        virtual void writeByteToDestination(byte b) = 0;

        virtual void writeByte(byte b) override
        {
            mBytesWritten++;
            writeByteToDestination(b);
        }
        //now, any derived class can override writeByteToDestination
        //and writeByte method will implement their code + increment the no. of written bytes
/*
        void getWrittenByteNumber(){
            cout << "Number of Bytes: " << mBytesWritten << endl;
        }
*/
};


//a class with deleted constructor is also an abstract class (usually a static class)
/*
class MathFunctions{
    //...

    public:
        MathFunctions() = delete;
        //...
};
*/




//----------Implementations------------//
class ConsoleBinaryWriter : public BinaryWriterBase /*IBinaryWriter*/
{
    public:
        void writeByteToDestination(byte b) override
        {
                cout << (b < 16 ? "0" : "") << std::hex << (int) b << " ";
        }

        virtual ~ConsoleBinaryWriter() override { }
};

class FileBinaryWriter : public BinaryWriterBase /*IBinaryWriter*/
{
    private:
        ofstream mFile;
    public:
        FileBinaryWriter(string fileName) : mFile(fileName){ }
        void writeByteToDestination(byte b) override
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

            //((BinaryWriterBase*)bw)->getWrittenByteNumber();
        }
};



int main()
{

    ConsoleBinaryWriter* cbw = new ConsoleBinaryWriter();
    FileBinaryWriter* fbw = new FileBinaryWriter("test.txt");

    IBinaryWriter *bw = fbw;

    bw -> writeByte(0xCD);

    bw = cbw;
    bw -> writeByte(0xCD);

    //BinaryWriterBase* bwb = cbw;
    //bwb -> getWrittenByteNumber();

    //Complex cp(13,25);

    //cp.write(bwb);


    delete bw;

    return 0;
}


/*
class destructable
{
    public:
        ~destructable()
        {
            cout <<  "destructable obj is destructed." << endl;
        }
};

*/


/*
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

*/
