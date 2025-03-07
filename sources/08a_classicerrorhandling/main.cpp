#include "classicerrorhandling.h"


// Call multiple functions that may fail
// Classic implementation
// CClassicErrorHandling::getNumericTableValueNegative is the core function of this example
// Compare to 08b_OptionalMonad and 09_ExpectedMonad

int main(int argc, char* argv[])
{
    using namespace mop;
    CClassicErrorHandling::testForNegativeNumericValue();
    return 0;
}
