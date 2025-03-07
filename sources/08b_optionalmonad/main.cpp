#include "optionalmonadtest.h"

// Call multiple functions that may fail
// Implementation using std::optional and monadic operations
// COptionalMonad::isNumericTableCellValueNegative is the core function of this example
// Compare to 08a_ClassicErrorHandling and 09_ExpectedMonad

int main(int argc, char* argv[])
{
    using namespace mop;

    COptionalMonadTest::testForNegativeNumericValue();

    return 0;
}
