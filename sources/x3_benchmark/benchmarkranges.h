#ifndef BENCHMARKRANGES_H
#define BENCHMARKRANGES_H

#include <vector>

namespace mop
{

// Create the "expand to iota 3x" vector, then +/- accumulate for a single result - classic loop
int accumulatePlusMinusExpandedIotaClassic(const std::vector<int>& input);

int accumulatePlusMinusExpandedIotaClassicPreallocate(const std::vector<int>& input);

// Same as above, but building the final result in the loop, therefore avoiding costly vector storage
int accumulatePlusMinusExpandedIotaClassicIntegrated(const std::vector<int>& input);

// Create the "expand to iota 3x" view, then +/- accumulate for a single result using std::ranges::views
int accumulatePlusMinusExpandedIotaViews(const std::vector<int>& input);

// Same as above, but passing a vector between functions instead of a view
int accumulatePlusMinusExpandedIotaViewsToVector(const std::vector<int>& input);

// Create the "expand to iota 3x" vector, then find the first index of the maximum value in 'input' within the result vector
std::size_t findMaxValueIndexInExpandedIotaClassic(const std::vector<int>& input);

// Same as above, but building the final result in the loop, therefore avoiding costly vector storage
std::size_t findMaxValueIndexInExpandedIotaClassicIntegrated(const std::vector<int>& input);

// Create the "expand to iota 3x" view, then find the first index of the maximum value in 'input' within the result vector
std::size_t findMaxValueIndexInExpandedIotaViews(const std::vector<int>& input);

// Same as above, but passing a vector between functions instead of a view
std::size_t findMaxValueIndexInExpandedIotaViewsToVector(const std::vector<int>& input);

std::size_t findMaxValueIndexInRange(auto&& range, const int maxValue)
{
    size_t index=0;
    for(const auto& value : range)
    {
        if (value == maxValue)
        {
            break;
        }
        ++index;
    }
    return index;
}

}

#endif // BENCHMARKRANGES_H
