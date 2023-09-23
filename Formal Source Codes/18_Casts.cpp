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

// *************
// *** C++ CASTS
// *************

// An expression written as
//     (T) E
// casts the expression E to type T. This kind of cast is known as a ``C-style
// cast'' in C++.
//
// An expression written as
//     T(E)
// also casts E to type T, if the type T is primitive (as in int(5.f)). Such a
// cast is known as a ``function-style'' cast. Notice how the syntax mimics a
// constructor call to create a temporary object.
//
// However, the preferred method of casts is actually different in C++. Other
// than the C-style and the function-style casts, there are four types of casts
// in C++, which are called the ``C++-style casts'':
//     - static_cast
//     - dynamic_cast
//     - reinterpret_cast
//     - const_cast
// The general syntax for these casts is:
//     *_cast<T>(E)
// In general, it is advised to prefer C++-style casts over the C-style and the
// function-style ones, as these casts convey the rationale behind the cast
// more clearly and have more safety checks.
//
// We exemplify them below.

// A parent class that contains a single integer field with a getter and an
// increment method.
class Parent
{
    protected:
        int mValue;

    public:
        Parent() : mValue(0)
        {
        }

        int getValue() const
        {
            return mValue;
        }

        void increment()
        {
            mValue++;
        }

        // For our upcoming dynamic_cast example to work, we need to make this
        // parent class polymorphic (i.e., have a virtual function).
        // Non-polymorphic types do not contain any RTTI data (a concept we
        // explain below).
        virtual void dummyVirtualFunctionToMakeParentPolymorphic() {}
};

// A child class extending the parent with a decrement operation.
class Child : public Parent
{
    public:
        void decrement()
        {
            mValue--;
        }
};

// A class that contains a pair of private integers with getters.
class PairOfIntegers
{
    private:
        const int mFirst;
        const int mSecond;

    public:
        PairOfIntegers(int f, int s) : mFirst(f), mSecond(s)
        {
        }

        int getFirst() const { return mFirst; }
        int getSecond() const { return mSecond; }
};


void castToParentAndIncrement(Child &c)
{
    // In general, one should primarily ``static_cast<>'' to cast between any
    // types in C++. This kind of cast:
    //     - Guarantees not to change the const qualifier.
    //     - Guarantees that the types are compatible.
    // A ``static cast'' does not make any decisions at runtime. The mechanics
    // of the cast are completely determined at compile-time.
    //
    // Below, we are casting a Child reference to a Parent reference with a
    // static cast. In general, casting Child references to Parent references
    // are safe. This is because every Child is a Parent (IS-A relationship).
    // Of course, we could also cast a Child pointer to a Parent pointer with
    // the same type of cast.
    Parent &p = static_cast<Child &>(c);
    p.increment();
}

void castToChildAndDecrement(Parent &p)
{
    // However, one can also cast a Parent reference (pointer) to the Child.
    // Such a cast is safe only if the programmer implements the programmatic
    // mechanisms to ensure that the instance pointed by the Parent reference
    // (or pointer) is always a Child instance.
    Child &c = static_cast<Child &>(p);
    c.decrement();
}

void checkCastToChildAndDecrement(Parent &p)
{
    // When we want to cast a Parent to a Child, but we are not sure if the
    // Parent pointer actually points to a Child, we can use ``dynamic_cast<>''.
    // ``Dynamic casts'' make use of a compiler feature widely known as
    //     ``Run-time Type Identification'' (RTTI)
    // This is enabled in GCC and Clang by default. When RTTI is enabled, each
    // instance of a polymorphic class (a class with virtual functions) contains
    // a pointer to a data structure that describes the details of the type.
    // (Very likely, the vtable pointer is re-used for that purpose).
    //
    // RTTI enables us to determine the original type of an instance at
    // run-time. The dynamic cast succeeds if the cast reference (pointer)
    // really points to an instance of the desired type (or one of its child
    // types). Otherwise, the cast fails and
    //     - Returns nullptr if the cast is to a pointer, or
    //     - Throws a std::bad_cast exception if the cast is to a reference.
    //
    // Below, we do a dynamic cast from Parent to Child. The cast returns
    // nullptr, if the instance is not Child.
    Child *c = dynamic_cast<Child *>(&p);

    // We only decrement after we make sure that the instance is a Child.
    if (c != nullptr)
    {
        c->decrement();
    }
}

void ignoreConstAndIncrement(const Parent &cp)
{
    // ``const_cast<>'' is used for changing the const qualifier on types. It
    // possible to both add and remove the qualifier. Removing the const
    // qualifier (as below) is only possible via this type of cast. However,
    // removal of const is usually considered bad practice.
    Parent &p = const_cast<Parent &>(cp);
    p.increment();
}

void zeroOutPairOfIntegers(PairOfIntegers &poi)
{
    // When we want to assign a new base type to a pointer without changing its
    // value, we use ``reinterpret_cast<>''. In the example below, there is no
    // logical cast possible from a PairOfIntegers* to int*. Therefore, the
    // other C++ casts will not work.
    //
    // Notice that using the reinterpret_cast<> gives us a way to access the
    // memory of an object, even if the object has private members.
    int *a = reinterpret_cast<int *>(&poi);
    a[0] = 0;
    a[1] = 0;

    // [IMPORTANT] One should NOT use reinterpret_cast<> to cast between parent
    // and child types. Casts between parent-child classes may alter the value
    // of the pointer and should be done via static_cast<> or dynamic_cast<>.
}

int main()
{
    const Parent p1;
    ignoreConstAndIncrement(p1);

    Child c2;
    castToParentAndIncrement(c2);

    Child c3;
    Parent & p3 = c3;
    castToChildAndDecrement(p3);

    Parent p4;
    checkCastToChildAndDecrement(p4);

    PairOfIntegers poi(1, 2);
    zeroOutPairOfIntegers(poi);

    return 0;
}
