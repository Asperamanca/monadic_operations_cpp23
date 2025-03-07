#include "classicerrorhandling_exceptions.h"

// Call multiple functions that may fail
// Implemented using exceptions
// Only briefly mentioned in introduction - not one of the main examples!
int main(int argc, char* argv[])
{
    using namespace mop;

    CClassicErrorHandlingExceptions::testForNegativeNumericValue();
    return 0;
}
