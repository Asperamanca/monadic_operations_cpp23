#include "pointerclassic.h"

// Repeat the example for "classic error handling", but this time,
//  functions return pointers instead of writing to an 'out' reference parameter.
// Each of the functions may fail, so we need to check pointers at every step
int main(int argc, char* argv[])
{
    using namespace mop;

    CPointersClassic::testForNegativeNumericValue();
    return 0;
}
