#include "pointermonad.h"

// Call a series of functions returning pointers, this time using a pointer monad
//  that takes care of nullptr checks
// Compare to 12a_PointerClassic
int main(int argc, char* argv[])
{
    using namespace mop;

    CPointerMonad::testForNegativeNumericValue();
    return 0;
}
