#include "purefunctions.h"
#include <ranges>
#include <vector>
#include <algorithm>
#include <cfenv>
#include <cmath>

#include "../common/printutils.h"

namespace mop
{

inline auto pureFunctionsGetMultipliedView(auto&& input, int multiplier)
{
    auto fMultiply = [&](const int number)
        {
            return number*multiplier;
        };

    return std::views::transform(std::forward<decltype(input)>(input), fMultiply);
}

void CPureFunctions::testNonPureFunctionProblem()
{
    const auto input = std::vector{2,4,6};
    auto multipliedView = pureFunctionsGetMultipliedView(input, 2);

    auto fPrint = [](const int& number)
        {
            printlnWrapper("{:}",number);
        };
    // Will print pretty random-looking numbers due to use of a dangling reference
    std::ranges::for_each(multipliedView,fPrint);
}


inline auto pureFunctionsGetMultipliedViewFixed(auto&& input, int multiplier)
{
    auto fMultiply = [multiplier](const int number)
        {
            return number*multiplier;
        };

    return std::views::transform(std::forward<decltype(input)>(input), fMultiply);
}

void CPureFunctions::testNonPureFunctionProblemFixed()
{
    const auto input = std::vector{2,4,6};
    auto multipliedView = pureFunctionsGetMultipliedViewFixed(input, 2);

    auto fPrint = [](const int& number)
        {
            printlnWrapper("{:}",number);
        };
    // Will print the correct numbers
    std::ranges::for_each(multipliedView,fPrint);
}

void CPureFunctions::testSinPurity()
{
    // Shows how std::sin can be influenced by global state, and is thus not pure
    std::fesetround(FE_DOWNWARD);
    printlnWrapper("Sin 0.9 (downward) {:}", std::sin(0.9));
    std::fesetround(FE_UPWARD);
    printlnWrapper("Sin 0.9 (upward) {:}", std::sin(0.9));
}

} // namespace mop

