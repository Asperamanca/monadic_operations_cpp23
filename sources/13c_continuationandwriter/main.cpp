#include "testcontinuationwriter.h"

// Shows how to combine continuation and writer monads
//  to get lock-free tracing in a pipeline running in threads
int main(int argc, char* argv[])
{
    using namespace mop;
    CTestContinuationWriter::testContinuationWithWriterExternalTrace();
    CTestContinuationWriter::testContinuationWithWriterOwnTrace();
    return 0;
}
