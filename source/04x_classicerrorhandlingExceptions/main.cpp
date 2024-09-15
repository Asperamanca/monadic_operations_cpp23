#include "classicerrorhandling_exceptions.h"

// Call multiple functions that may fail
// Implemented using exceptions
int main(int argc, char* argv[])
{
    CClassicErrorHandlingExceptions::testForNegativeNumericValue();
    CClassicErrorHandlingExceptions::testForValueComparison();
    return 0;
}
