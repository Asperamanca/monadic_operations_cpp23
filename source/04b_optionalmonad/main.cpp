#include "optionalmonad.h"

// Call multiple functions that may fail
// Implementation using std::optional and monadic operations
// COptionalMonad::isNumericTableCellValueNegative is the core function of this example
// Compare to 04a_ClassicErrorHandling and 04c_ExpectedMonad

int main(int argc, char* argv[])
{
    COptionalMonad::testForNegativeNumericValue();
    COptionalMonad::testForValueComparison();

    return 0;
}
