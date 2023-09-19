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

#include "PremiumAccount.h"

PremiumAccount::PremiumAccount(std::string ownerName, float threshold)
    : Account(ownerName), mThreshold(threshold)
{
}

float PremiumAccount::getThreshold() const
{
    return mThreshold;
}

/*virtual*/ void PremiumAccount::deposit(float amount) /*override*/
{
    Account::deposit(amount);

    if (amount >= mThreshold)
    {
        mBalance += 1.f;
        mLog += "reward(1.00)\n";
    }
}
