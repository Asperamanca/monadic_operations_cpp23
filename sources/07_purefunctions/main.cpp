#include "purefunctions.h"

// Example from "pure functions" section
int main(int argc, char* argv[])
{
    using namespace mop;

    CPureFunctions::testNonPureFunctionProblem();
    CPureFunctions::testNonPureFunctionProblemFixed();
    CPureFunctions::testSinPurity();

    return 0;
}
