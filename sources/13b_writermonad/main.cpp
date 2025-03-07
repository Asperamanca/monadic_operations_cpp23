#include "testwriter.h"

// Shows usage of a writer monad, which adds trace information to a pipeline
//  The writer passes trace information from stage to stage in a pipeline, and
//  allows us to add trace entries in every step. At the end of the pipeline, we
//  can collect both result and trace information at the end
int main(int argc, char* argv[])
{
        using namespace mop;

    // See testwriter.h for brief explanation what each test function exhibits
    // See testwriter.cpp to see how the writer monad is used
    // See writermonad.h for  information how the monad works
    CTestWriter::testWriterWithoutTrace();
    CTestWriter::testWriterWithExternalTrace();
    CTestWriter::testWriterWithOwnTrace();
    return 0;
}
