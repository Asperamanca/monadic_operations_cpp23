
#include "../common/printutils.h"
#include "testfunctor.h"

namespace mop
{

// Example for using functors
// ("classic loop" versions come first, for comparison)
// Look at the functions starting with "test" and "extra"

// This is a "function object", sometimes called a functor
// But it is not the functor we are looking for...
class CNegator
{
public:
    int operator()(const int value) const
    {
        return -value;
    }
};

} // namespace mop

int main(int argc, char* argv[])
{
    using namespace mop;
    // In this example, we follow a sequence of operations, in our case one calculation and one formatting
    //  We start with a radius, calculate the area of a circle, and format the result as a string.

    // The first three functions show 'classic' implementations not using functors
    // We show how to handle a single plain value,  a vector<value> and optional<value> respectively
    intro01ClassicSingleValue();
    intro02ClassicVector();
    intro03ClassicOptionalValue();

    // Now we repeat the same, but using a functor that lifts the existing functions
    //  (=creates new functions with extended capabilities out of the existing ones)
    intro11FunctorLiftSingleValue();
    intro12FunctorLiftVector();
    intro13FunctorLiftOptionalValue();

    // This time, we use a container-like wrapper functor
    intro21FunctorWrapperSingleValue();
    intro22FunctorWrapperVector();
    intro23FunctorWrapperOptionalValue();

    // We go one step further, and use a templetized functor
    intro31FunctorTemplateSingleValue();
    intro32FunctorTemplateVector();
    intro33FunctorTemplateOptionalValue();

    // We show that functors preserves composition
    intro41FunctorShowComposition();
    // We show that functors preserve identity
    intro42FunctorShowIdentity();

    // std::ranges::views exmple
    // First showing example with raw loops, then with ranges::views
    // They all do the same thing. Jump to the implementation to see how.
    introRanges01Classic();
    introRanges02FunctorView();
    introRanges03FunctorViewWithPipe();
    printStringRange(introRanges05ConvertViewResultToContainer());

    // extra1_FunctorVectorDoublePowToStr();

    // _x2_testDanglingReference();     // Depending on compiler / build options it may crash or worse.

    return 0;
}


