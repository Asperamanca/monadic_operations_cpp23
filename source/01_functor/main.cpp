
#include "../common/printutils.h"
#include "testfunctor.h"


// Example for using functors
// ("classic loop" versions come first, for comparison)
// Look at the functions starting with "test" and "extra"

// Not the functor we are looking for...
class CNegator
{
public:
    int operator()(const int value) const
    {
        return -value;
    }
};



int main(int argc, char* argv[])
{
    // They all do the same thing. Jump to the implementation to see how.
    test01_DoublePowToStrClassic();
    test02_DoublePowToStrClassicWithFunctions();
    test03_DoublePowToStrFunctorView();
    test04_DoublePowToStrFunctorViewWithPipe();
    printStringRange(test05_convertViewResultToContainer());

    extra1_FunctorVectorDoublePowToStr();
    // _x2_testDanglingReference();     // Depending on compiler / build options it may crash or worse.

    return 0;
}


