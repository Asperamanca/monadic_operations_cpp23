#ifndef TESTCONTINUATION_H
#define TESTCONTINUATION_H


namespace mop
{


class CTestContinuation
{
public:
    // Starting slow functions without concurrency
    static void noConcurrency();

    // Shows that creation of a future is almost instant, then we can choose to block and wait for the result (or not)
    static void singleValueContinuation();

    // Loop processing several values without concurrency
    static void loopNoConcurrenty();

    // Loop processing several values that uses the continuation monad
    static void loopContinuation();
};

} // namespace mop

#endif // TESTCONTINUATION_H
