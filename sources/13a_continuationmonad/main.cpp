#include "testcontinuation.h"


// Shows how a small pipeline of slow operations can be offloaded
//  to thread(s) using a continuation monad (QtConcurrent's implementation using QFuture)
int main(int argc, char* argv[])
{
    using namespace mop;

    CTestContinuation::noConcurrency();
    CTestContinuation::singleValueContinuation();
    CTestContinuation::loopNoConcurrenty();
    CTestContinuation::loopContinuation();

    return 0;
}
