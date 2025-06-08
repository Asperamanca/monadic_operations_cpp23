#ifndef CONFIGURERANGES_H
#define CONFIGURERANGES_H

#include <cstddef>
#include "rangesutilities.h"

namespace mop
{

// Size of initial input
static constexpr std::size_t s_RangesInputLength = 50;
// Size of the intermediate range (before folding to a single result)
static constexpr std::size_t s_RangesIntermediateLength = calculateRangeSize(s_RangesInputLength);
// Number of iterations for the test
static constexpr int s_RangesIterations = 1000;

} // namespace mop

#endif // CONFIGURERANGES_H
