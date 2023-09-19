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

// *************************
// *** BASIC NAMESPACE USAGE
// *************************

// No namespace is also called the ``global namespace''.
// This particular sort function is in the global namespace.
void sort()
{
}

// This is the namespace for Lib1.
namespace Lib1
{
    void sort() // Gets the fully qualified name ``Lib1::sort''.
    {
    }
}

// It is possible to append definitions/declarations
// to a namespace.
namespace Lib1
{
    void search() // Lib1::search.
    {
        sort(); // Refers to Lib1::sort(), since we are in the block of
                // Lib1 namespace.
    }
}

// We can nest namespaces.
namespace Lib1
{
    namespace SubLib1
    {
        void find() // Lib1::SubLib1::find.
        {
        }
    }
}

// Lib2
namespace Lib2
{
    void sort() // Lib2::sort.
    {
    }
}

int main(int argc, char **argv)
{
    // Specific access to the sort() functions.
    Lib1::sort(); // Calls sort() of Lib1.
    Lib2::sort(); // Calls sort() of Lib2.
    ::sort(); // Calls our sort() in the global namespace.

    {
        sort(); // Calls the sort() in the global namespace,
                // as there are no ``using'' declarations in this block.
                // ``using'' declarations only apply within the block.
    }

    {
        using Lib1::sort;

        sort(); // Calls sort() of Lib1, due to the ``using'' declaration.
        
        ::sort(); // Calls the global sort().

        // search(); // Cannot access search() without specifying the
                     // namespace, as the ``using'' declaration above
                     // only imports sort() from Lib1. This code
                     // would not compile.
    }

    {
        using namespace Lib1;

        // sort(); // Call to sort() is now ambiguous, it may refer
                   // to either ::sort() or Lib1::sort(). This code
                   // would not compile.
        

        search(); // Calls search() of Lib1, due to the using declaration.
                  // The ``using namespace'' declaration above imports all
                  // identifiers from Lib1.
        
        SubLib1::find(); // We can also directly refer to the sub-namespace
                         // due to the ``using namespace'' declaration.
    }

    return 0;
}
