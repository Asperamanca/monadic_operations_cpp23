#include "expectedmonad.h"

// Call multiple functions that may fail
// Implementation using std::expected and monadic operations
// CExpectedMonad::isNumericTableCellValueNegative is the core function of this example
// Compare to 04a_ClassicErrorHandling and 04b_OptionalMonad

int main(int argc, char* argv[])
{
    CExpectedMonad::testForNegativeNumericValue();
    CExpectedMonad::testForValueComparison();

    return 0;
}
