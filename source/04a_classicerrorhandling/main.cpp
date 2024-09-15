#include "classicerrorhandling.h"


// Call multiple functions that may fail
// Classic implementation
// CClassicErrorHandling::getNumericTableValueNegative is the core function of this example
// Compare to 04b_OptionalMonad and 04c_ExpectedMonad

int main(int argc, char* argv[])
{
    CClassicErrorHandling::testForNegativeNumericValue();
    CClassicErrorHandling::testForValueComparison();
    return 0;
}
