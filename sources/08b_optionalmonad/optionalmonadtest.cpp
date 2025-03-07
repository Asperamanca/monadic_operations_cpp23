#include "optionalmonadtest.h"
#include "optionalmonad.h"
#include <cmath>
#include <optional>

namespace mop
{

void COptionalMonadTest::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        auto oValue = COptionalMonad::isNumericTableCellValueNegative(db, 10,CCellLocation{.m_Column=1, .m_Row=1});
        printlnWrapper("HasValue: {:} Value: {:}",oValue.has_value(),oValue.value_or(false));
    }

    // NOK Case
    {
        auto oValue = COptionalMonad::isNumericTableCellValueNegative(db, 10,CCellLocation{.m_Column=2, .m_Row=1});
        printlnWrapper("HasValue: {:} Value: {:}",oValue.has_value(),oValue.value_or(false));
    }
}

std::optional<double> sqrtIfPossible(const double input)
{
    if (input < 0.0)
    {
        return {};
    }
    return std::sqrt(input);
}

void COptionalMonadTest::testOptionalUsage()
{
    std::optional<double> result1 = sqrtIfPossible(5.5);
    if (result1.has_value())
    {
        printlnWrapper("Sqrt of 5.5 is {:}",result1.value());
    }

    if (auto result2 = sqrtIfPossible(3.3))
    {
        // Use result
    }

    auto result3 = sqrtIfPossible(-454).value_or(0.0);
    // Use result
    std::ignore = result3;
}

void COptionalMonadTest::testJoinFromAndThenWithIdentity()
{
    auto wrapped = std::optional<std::optional<int>>{5};
    auto unwrapped = wrapped.and_then(std::identity{});
    // Type of 'start': std::optional<std::optional<int>>
    // Type of 'end'  :               std::optional<int>
    // I 'joined' by using and_then (=a "monadic bind") and an identity function
    //...now I get optional<int> only
    std::ignore = unwrapped;
}


} // namespace mop

