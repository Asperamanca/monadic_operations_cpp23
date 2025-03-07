#ifndef TESTCONTINUATIONWRITER_H
#define TESTCONTINUATIONWRITER_H

#include "../13b_writermonad/writermonad.h"

namespace mop
{

class CTestContinuationWriter
{
public:
    // Traced, slow version of calculateArea
    static CWriterValueAndTrace<double> calculateAreaTraced(const double radius);
    // Traced, slow version of formatArea
    static CWriterValueAndTrace<std::string> formatAreaTraced(const double area);

    // Shows how to combine continuation+writer for a single value,
    //  with the trace information added as part of the pipeline (not from the called functions)
    static void testContinuationWithWriterExternalTrace();
    // Shows how to combine continuation+writer for a single value,
    //  with the trace information provided by the functions we call
    static void testContinuationWithWriterOwnTrace();

    // Shows how to use the continuation+writer combination on a sequence (vector) of values
    static void testContinuationSequenceWithWriter();
};

} // namespace mop

#endif // TESTCONTINUATIONWRITER_H
