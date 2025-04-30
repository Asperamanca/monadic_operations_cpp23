#ifndef RANGESUTILITIES_H
#define RANGESUTILITIES_H

#include <vector>
#include <ranges>
#include <numeric>

namespace mop
{

// Expand a number to a view of {1...number}
inline auto expandIotaView(const int number)
{
    return std::views::iota(1,number+1);
}

inline auto expandIotaVector(const int number)
{
    std::vector<int> result(number);
    // std::ranges::iota(result.begin(), result.end(),1);
    std::iota(result.begin(), result.end(),1);
    return result;
}

// Expand all numbers in input to views of {1...number}, repeat twice
inline auto expandIotaViews(const std::vector<int>& input)
{
    return input
            | std::views::transform(expandIotaView)
            | std::views::join
            | std::views::transform(expandIotaView)
            | std::views::join
            | std::views::transform(expandIotaView)
            | std::views::join;
}


std::vector<int> expandIotaViewsToVector(const std::vector<int>& input);

// Expand all numbers in input to sequences of {1...number}, repeat twice
std::vector<int> expandIotaClassic(const std::vector<int>& input);

// Accumulate a range, alternating between adding and substracting a value
inline int accumulatePlusMinus(auto&& range)
{
    int result = 0;
    int sign = 1;
    for(const auto& value : range)
    {
        result += (value*sign);
        sign = -sign;
    }
    return result;
}


} // namespace mop


#endif // RANGESUTILITIES_H
