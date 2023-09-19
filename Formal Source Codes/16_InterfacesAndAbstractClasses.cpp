//
// Middle East Technical University
// Dept. of Computer Engineering
//
// CENG 213 - Data Structures
// Dr. Hakan YILDIZ
// hakan@ceng.metu.edu.tr
//
// Not to be reshared without permission.
//

// ***********************************
// *** INTERFACES AND ABSTRACT CLASSES
// ***********************************

#include <fstream>
using std::ios;
using std::ofstream;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

// The definition of a ``byte'' data type used by this example.
typedef unsigned char byte;

// A useful application of polymorphism is ``interfaces''.  In C++, an
// ``interface'' is a class that (mainly) consists of virtual functions with no
// implementations. Such functions are called ``pure virtual'' functions. The
// lack of implementation in interfaces is intentional. The goal is to allow
// other programmers to
// - Write classes that ``implement'' the interface by overriding the pure
//   virtual functions with their own implementation, and
// - Write code against the interface (i.e. call the interface's virtual
//   functions), without knowing how the interface is going to be implemented.
//
// Interfaces are the standard way of achieving modularity and interoperation
// between software components in OOP.
//
// Interfaces are good examples of a larger set of classes known as
// ``abstract'' classes. An ``abstract'' class is a class which cannot be
// instantiated (i.e., whose instances cannot be constructed). A class T may
// become abstract due to the following reasons:
//     - A pure virtual function f() is declared in T. Then, T itself does not
//       support one of its own functions and thus its definition is incomplete.
//       T itself cannot be instantiated but a child class of T that overrides
//       f() may.
//     - Not having a constructor for T. This happens when you intentionally
//       delete the implicit constructors. This is usually done to create a
//       class that only offers static methods. In fact, there is an easier way
//       to achieve the same effect in C++: one can use the ``static'' keyword
//       on a class declaration to prevent it from having constructors and
//       instance methods. For example:
//           static class MathFunctions
//           {
//               static float power(float base, float exponent);
//               static float log(float power, float base);
//               ...
//           };
//
// If a class is not abstract, then it is called to be ``concrete''.
//
// The following is an interface that represents an object that can write binary
// data (bytes) to some destination. Depending on how this interface is
// implemented, the destination can be the terminal, a file, a network
// connection, another memory location, a hardware device, etc. (Observe the
// flexibility.) Also, any additional logic (such as keeping statistics) can be
// hidden behind this interface.
class IBinaryWriter
{
    public:
        // The following ``writeByte'' function is ``pure virtual'' because it
        // is declared with `` = 0''. This tells the compiler that this
        // function will not have a definition, until a child class overrides
        // and implements it. Notice that the introduction of a pure virtual
        // function still creates a virtual function table for the class. In
        // other words, the instances of this class contain of a hidden
        // ``vtable'' field and thus they occupy memory.
        //
        // Notice that any child class that wants to be ``concrete'' has to
        // implement this function.
        virtual void writeByte(byte b) = 0;

        // The following is a ``virtual destructor'' for the class. In other
        // words, this interface has a destructor and its overridable. Not all
        // interfaces require this; it depends on how the ``ownership'' of the
        // interface instances are managed. If it is possible to ``lose the type
        // information'' between when an instance is created and when it is
        // destroyed, a virtual destructor is necessary. We elaborate on this
        // later.
        //
        // Let us also note that, even though our destructor has no logic in it,
        // we are unable to declare it as a pure virtual function. An (implicit
        // or explicit) destructor (generally) has to be present in all classes
        // from which concrete classes are derived. In C++, by design, the
        // destructor of a child class is chained to the parent's destructor.
        virtual ~IBinaryWriter() {};
};

// Interfaces are not the only abstract classes. It is possible to define a
// class that has only a portion of its functions as pure virtual. Below, we
// define such a class BinaryWriterBase, which will serve as the base class for
// more specific IBinaryWriter implementations. We put some common logic to this
// class (such as keeping track of the count of bytes written), so that this
// logic is not replicated in the child classes.
class BinaryWriterBase : public IBinaryWriter
{
    private:
        // Instance member variable to keep track of the count.
        unsigned mBytesWritten;

    public:
        // Constructor for the class. Having a constructor does not mean that
        // the class is concrete. The class will be abstract if there are
        // non-overridden pure virtual functions or the class itself introduces
        // pure virtual functions.
        BinaryWriterBase() : mBytesWritten(0)
        {
        }

        // The getter for mBytesWritten.
        unsigned getBytesWritten() const
        {
            return mBytesWritten;
        }

        // Override for IBinaryWriter::writeByte. Here, we use two specifiers
        // ``override'' and ``final''.
        //
        // The ``override'' specifier is optional and tells the compiler that
        // we want to override a function of the base class. The compiler will
        // check if the declaration is really an override and give an error if
        // it is not. It is good practice to use this specifier for all
        // overrides; it prevents us from making any errors during the override
        // (such as misspelling the function name).
        //
        // To ensure that the derived classes run the common logic, we added
        // ``final'' specifier. This specifier prevents any child classes from
        // further overriding the function. In other words, the child classes
        // are now forced to run this logic when writeByte() is called.
        //
        // Finally, note that the use of ``virtual'' in this declaration is
        // optional. The function is implicitly virtual since it is an override.
        void writeByte(byte b) override final
        {
            // Update statistics.
            mBytesWritten++;

            // We now want to write the byte to the destination. However, in
            // this base class, we want to defer the logic of writing the byte
            // to the child class. This is easily achieved by introducing
            // a new pure virtual function writeByteToDestination(), which is
            // to be implemented by the children. It is declared below.
            writeByteToDestination(b);
        }

    protected:
        // Here, we declare the pure virtual writeByteToDestination() function.
        // Since we do not expect the outside code to call this function
        // directly, we declare it under the ``protected'' access modifier.
        // Using ``private'' is not possible here because the child classes need
        // to override this function.
        //
        // Notice that any child class of BinaryWriterBase has to implement this
        // function if it wants to be concrete.
        virtual void writeByteToDestination(byte b) = 0;

        // Our destructor overriding ~IBinaryWriter(). There would already be an
        // implicit one if we did not write this one.
        ~BinaryWriterBase() override
        {
            cout << "Destroying binary writer instance... "
                 << "Bytes written: " << mBytesWritten << "." << endl;
        }
};

// Implementation of a binary writer writing to the console.
class ConsoleBinaryWriter : public BinaryWriterBase
{
    protected:
        void writeByteToDestination(byte b) override final
        {
            // Writes the byte to the console in hex form.
            cout << (b < 16 ? "0" : "") << std::hex << (int) b << " ";
        }
};

// Implementation of a binary writer writing to a file.
class FileBinaryWriter : public BinaryWriterBase
{
    private:
        ofstream mFile;

    public:
        FileBinaryWriter(string filename)
            : mFile(filename, ios::binary) // The file is opened upon
                                           // construction. It will be closed
                                           // when the ofstream object is
                                           // destroyed upon our destruction.
        {
        }

    protected:
        void writeByteToDestination(byte b) override final
        {
            mFile.put(b);
        }
};

// Another interface that represents objects that can be written in binary form,
// through an IBinaryWriter.
class IBinaryData
{
    public:
        virtual void write(IBinaryWriter &w) const = 0;
};

// A simple integer-based complex class that implements IBinaryData.
class Complex : public IBinaryData
{
    private:
        const int mReal;
        const int mImag;

    public:
        Complex(int r, int i) : mReal(r), mImag(i) {};
        int getReal() const { return mReal; }
        int getImag() const { return mImag; }

        void write(IBinaryWriter &w) const override final
        {
            for (unsigned i = 0; i < sizeof(mReal); i++)
            {
                w.writeByte(((byte *)&mReal)[i]);
            }
            
            for (unsigned i = 0; i < sizeof(mImag); i++)
            {
                w.writeByte(((byte *)&mImag)[i]);
            }

            // Notice that the Complex object has no idea of where the data is
            // written, how it is written and if any additional actions are
            // taken. This is the point of interfaces. IBinaryWriter defines an
            // interface where different code can be connected through. The
            // implementation to use for the interface can be determined at
            // run-time. Interfaces are one of the mechanisms that make it easy
            // to write ``plug-in'' modules that can loaded and used at runtime.
        }
};

// [NOTE] In this example, we have split our logic into two:
//            - A common logic in the base class.
//            - Specialized logics in the child classes.
//        Such a code implements ``specialization'' by ``inheritance''. The main
//        point of this approach is to avoid ``redundant'' logic. An alternative
//        approach to the same problem is known as ``specialization by
//        composition''. We will not exemplify it here, but you can get more
//        information if you search the web for ``inheritance vs composition''.

int main()
{
    // We create a ConsoleBinaryWriter and a FileBinaryWriter instance and
    // assign their address to IBinaryWriter pointers.
    IBinaryWriter *cbw = new ConsoleBinaryWriter;
    IBinaryWriter *fbw = new FileBinaryWriter("test.txt");

    // At this point, the type information for the instances is mostly lost. The
    // compiler has no idea about the original types of the objects pointed
    // by ``cbw'' and ``fbw''. It only knows that they implement IBinaryWriter.

    Complex c(0x01234567, 0x07654321);

    c.write(*cbw); // We deference to convert the pointer to an l-value whose
                   // reference can be taken and passed to write(). (Yes, we
                   // are passing in the same pointer but in reference form).
    c.write(*fbw);

    cout << endl;

    // This code invokes the virtual destructor of IBinaryWriter. Since it is
    // virtual, it actually invokes the overriding ~ConsoleBinaryWriter().
    // Notice that we have no compile-time information of the original type
    // pointed by cbw at this point.
    delete cbw;

    // Similarly, invokes ~FileBinaryWriter(). Notice that invocation of this
    // overriding destructor is crucial; the member``mFile'' would not be
    // destroyed otherwise and thus the file would be kept open. (If the file is
    // not properly closed, it is possible that some data will not make it to
    // the file).
    delete fbw;

    cout << endl;

    return 0;
}
