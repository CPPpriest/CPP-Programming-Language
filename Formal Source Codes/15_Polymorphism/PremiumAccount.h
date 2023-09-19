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

// ****************
// *** POLYMORPHISM
// ****************

// We use the same Account and PremiumAccount classes that we used in our last
// example, with the following changes:
// - The deposit() function in Account is now is declared as a ``virtual''
//   function.
// - The deposit() function in PremiumAccount includes an ``override''
//   specifier.

#include "Account.h"

class PremiumAccount : public Account
{
    private:
        const float mThreshold;

    public:
        PremiumAccount(std::string ownerName, float threshold);

        float getThreshold() const;

        // Despite not using the virtual keyword, the deposit() function is
        // also virtual function for PremiumAccount. In other words, a child
        // class of PremiumAccount can override it. The virtual keyword can
        // still be used here, but it would not have any effect.
        //
        // The declaration of this particular ``overriding'' deposit function
        // is necessary. The compiler will not allow us to write a new
        // implementation unless we declare it.
        // 
        // It is optional but advised to mark such any overriding function with
        // the specifier ``override'' specifier, as done below. The specifier
        // makes the compiler check that the function deposit() was indeed a
        // virtual function of the base class.
        void deposit(float amount) override;
};
