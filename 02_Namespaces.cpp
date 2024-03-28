
void sort() //Global sort function
{
}

namespace Lib1{

    void sort() //  Lib1::sort()
    {
    }
}

namespace Lib1{

    void foo(){
        sort(); //Refers to Lib1::sort()
            //Since they are in the same scope

        ::sort();   //Global sort()
    }
}



//Namespaces can be nested
namespace Lib3{
    namespace subLib3{

        void sort()
        {
        }

    }
}








int main()
{
    ::sort();   
    //Global Sort function is accessed through ::
    //without a namespace

    sort();         //Refers to Global sort() since there is no local one
    Lib1::sort();     //Refers to Lib1::sort()


    //block nested inside main, not a namespace which can be opened and access multiple times
    {
      sort(); //Refers to global sort()
    }

    {
      using Lib1::sort;
        //using namespace Lib1; 
          //---warning! Call is ambiguous!
          /*
            when using namespace statement is used
            for an identifier exist in both global and given namespace
            ambiguous identifier warning is returned to avoid wrong calls
            !!! Just a Safety feature, syntax is correct.   */
      sort();     
      //Refers to Lib1::sort()
      //Only within the block+
    }


    // Scope resolution for nested namespace
    Lib3::subLib3::sort();


    return 0;
}
