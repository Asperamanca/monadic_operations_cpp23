#ifndef OPTIONALMONADTEST_H
#define OPTIONALMONADTEST_H

namespace mop
{

class COptionalMonadTest
{
public:
    // Main example test case
    static void testForNegativeNumericValue();

    // Shows how you can use std::optional (check and access data)
    static void testOptionalUsage();

    // Shows how to use std::identity to get 'join' behavior from 'and_then'
    static void testJoinFromAndThenWithIdentity();
};



} // namespace mop

#endif // OPTIONALMONADTEST_H
