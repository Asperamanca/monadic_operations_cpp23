#ifndef TESTWRITER_H
#define TESTWRITER_H

namespace mop
{

class CTestWriter
{
public:
    // Shows how normal functions without trace information can be passed through the pipeline
    // This is mostly useful if only some functions in a pipeline are supposed to trace
    static void testWriterWithoutTrace();

    // Shows how minimal trace information can be added to normal functions that don't provide trace information themselves
    // Quick and easy way to add basic trace without changing existing function API
    static void testWriterWithExternalTrace();

    // Shows how to use the writer monad with functions that return trace information themselves
    // Requires you to change the return type of your functions, but allows you to trace whatever you like
    static void testWriterWithOwnTrace();
};

// NOTE: When adopting the writer monad on existing code, it makes sense to
// 1) Just build the pipeline without trace (see 'testWriterWithoutTrace')
// 2) Add minimal trace without changing functions (see 'testWriterWithExternalTrace')
// 3) Selectively change function signatures where more detailed tracing is necessary (see 'testWriterWithOwnTrace')

} // namespace mop

#endif // TESTWRITER_H
