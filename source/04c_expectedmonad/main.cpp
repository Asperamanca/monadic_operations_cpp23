#include "expectedmonad.h"

int main(int argc, char* argv[])
{
    CExpectedMonad::testForNegativeNumericValue();
    CExpectedMonad::testForValueComparison();

    return 0;
}
