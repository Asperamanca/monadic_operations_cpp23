#include "benchmarkranges.h"
#include "ctrack.hpp"
#include "rangesutilities.h"
#include "configureranges.h"

namespace mop
{

// Create the "expand to iota 3x" vector, then +/- accumulate for a single result - classic loop
int accumulatePlusMinusExpandedIotaClassic(const std::vector<int>& input)
{
    {
        CTRACK;
        auto vecForOutput = std::vector<int>{};
        auto vector = expandIotaClassic(input,std::move(vecForOutput));
        return accumulatePlusMinus(vector);
    }

}


int accumulatePlusMinusExpandedIotaClassicPreallocate(const std::vector<int>& input)
{
    constexpr size_t preallocSize = calculateRangeSize(s_RangesInputLength);
    auto vecForOutput = std::vector<int>{};
    vecForOutput.reserve(preallocSize);
    {
        CTRACK;
        auto vector = expandIotaClassic(input, std::move(vecForOutput));
        return accumulatePlusMinus(vector);
    }
}

// Same as above, but building the final result in the loop, therefore avoiding costly vector storage
int accumulatePlusMinusExpandedIotaClassicIntegrated(const std::vector<int>& input)
{
    CTRACK;
    int result = 0;
    int sign = 1;
    for(const int i : input)
    {
        for(int q=1;q<=i;++q)
        {
            for(int r=1;r<=q;++r)
            {
                for(int s=1;s<=r;++s)
                {
                    result += (s*sign);
                    sign = -sign;
                }
            }
        }
    }
    return result;
}


// Create the "expand to iota 3x" view, then +/- accumulate for a single result using std::ranges::views
int accumulatePlusMinusExpandedIotaViews(const std::vector<int>& input)
{
    CTRACK;
    auto view = expandIotaViews(input);
    return accumulatePlusMinus(view);
}

// Same as above, but passing a vector between functions instead of a view
int accumulatePlusMinusExpandedIotaViewsToVector(const std::vector<int>& input)
{
    CTRACK;
    auto vector = expandIotaViewsToVector(input);
    return accumulatePlusMinus(vector);
}


// Create the "expand to iota 3x" vector, then find the first index of the maximum value in 'input' within the result vector
std::size_t findMaxValueIndexInExpandedIotaClassic(const std::vector<int>& input)
{
    CTRACK;
    if (input.empty())
    {
        return {};
    }
    const int maxValue = std::ranges::max(input);
    auto vecPrealloc = std::vector<int>{};
    auto vector = expandIotaClassic(input,std::move(vecPrealloc));
    return findMaxValueIndexInRange(vector,maxValue);
}

// Same as above, but building the final result in the loop, therefore avoiding costly vector storage
std::size_t findMaxValueIndexInExpandedIotaClassicIntegrated(const std::vector<int>& input)
{
    CTRACK;
    if (input.empty())
    {
        return {};
    }
    const int maxValue = std::ranges::max(input);

    size_t index=0;
    for(const int i : input)
    {
        for(int q=1;q<=i;++q)
        {
            for(int r=1;r<=q;++r)
            {
                for(int s=1;s<=r;++s)
                {
                    if (s==maxValue)
                    {
                        return index;
                    }
                    ++index;
                }
            }
        }
    }

    return index;
}

// Create the "expand to iota 3x" view, then find the first index of the maximum value in 'input' within the result vector
std::size_t findMaxValueIndexInExpandedIotaViews(const std::vector<int>& input)
{
    CTRACK;
    if (input.empty())
    {
        return {};
    }
    const int maxValue = std::ranges::max(input);
    auto view = expandIotaViews(input);
    return findMaxValueIndexInRange(view,maxValue);
}

// Same as above, but passing a vector between functions instead of a view
std::size_t findMaxValueIndexInExpandedIotaViewsToVector(const std::vector<int>& input)
{
    CTRACK;
    if (input.empty())
    {
        return {};
    }
    const int maxValue = std::ranges::max(input);
    auto vector = expandIotaViewsToVector(input);
    return findMaxValueIndexInRange(vector,maxValue);
}





}


