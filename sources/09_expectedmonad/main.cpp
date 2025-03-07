#include "expectedmonad.h"

// Call multiple functions that may fail
// Implementation using std::expected and monadic operations
// CExpectedMonad::isNumericTableCellValueNegative is the core function of this example
// Compare to 08a_ClassicErrorHandling and 08b_OptionalMonad

int main(int argc, char* argv[])
{
    using namespace mop;

    CExpectedMonad::testForNegativeNumericValue();

    return 0;
}
