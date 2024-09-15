#include "testfunctor.h"
#include "../common/printutils.h"
#include <algorithm>
#include <ranges>
#include <format>
#include <cmath>

// Helper functions

std::string dblToStr(const double value)
{
    return std::format("{:}",value);
}

double makeSquared(const double value)
{
    return std::pow(value,2.0);
}

// Test functions

void test01_DoublePowToStrClassic()
{
    auto v = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    for(const auto& value : v)
    {
        strings.push_back(std::format("{:}",std::pow(value,2.0)));
    }
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printStringRange(strings);
}

void test02_DoublePowToStrClassicWithFunctions()
{
    auto v = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    for(const auto& value : v)
    {
        strings.push_back(dblToStr(makeSquared(value)));
    }
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printStringRange(strings);
}


void test03_DoublePowToStrFunctorView()
{
    auto v = std::vector{1.5,2.0,2.5};

    auto strings =
        std::views::transform(std::views::transform(v,makeSquared),
                              dblToStr);
    // {"2.25", "4", "6.25"}

    // Print type name of view
    printlnWrapper("{:}",typeid(strings).name());

    // Print output for testing
    printStringRange(strings);
}



void test04_DoublePowToStrFunctorViewWithPipe()
{
    auto v = std::vector{1,2,5,8};

    auto strings = v
                   | std::views::transform(makeSquared)
                   | std::views::transform(dblToStr);
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printStringRange(strings);
}

std::vector<std::string> test05_convertViewResultToContainer()
{
    using namespace std;
    auto v = vector{1.5,2.0,2.5};

    auto strings = v
                   | views::transform(makeSquared)
                   | views::transform(dblToStr);

#ifdef SUPPORTS_RANGES_TO
    return ranges::to<vector<string>>(strings);
#else
    return {strings.begin(), strings.end()};
#endif
}

void extra1_FunctorVectorDoublePowToStr()
{
    auto v = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    std::ranges::transform(v, std::back_inserter(strings),
                           [](const double value){return dblToStr(makeSquared(value));});
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printStringRange(strings);
}



struct CEntry
{
    int m_X{};
    int m_Y{};
    std::string m_Text{};
};


CEntry getNearestEntry(const int x)
{
    static std::vector s_Entries{CEntry{.m_X=0 ,.m_Y=5,.m_Text="Start"},
        CEntry{.m_X=3 ,.m_Y=2,.m_Text="A"},
        CEntry{.m_X=6 ,.m_Y=6,.m_Text="B"},
        CEntry{.m_X=7 ,.m_Y=0,.m_Text="C"},
        CEntry{.m_X=10,.m_Y=9,.m_Text="End"},};
    auto iter = std::lower_bound(s_Entries.cbegin(), s_Entries.cend(),x,
                                 [](const CEntry& item, const int cmp){return item.m_X < cmp;});
    if (iter == s_Entries.cend())
    {
        return s_Entries.back();
    }
    auto iterNext = std::next(iter);
    if (iterNext == s_Entries.cend())
    {
        return *iter;
    }

    if ((x - iter->m_X) <= (iterNext->m_X - x))
    {
        return *iter;
    }
    return *iterNext;
}

void extra2_DanglingReference()
{
    using namespace std;
    auto v = vector{1,3,7};

    auto strings = v
                   | views::transform(getNearestEntry)
                   | views::transform(&CEntry::m_Text); // Obtain reference to a temporary - the return value of getNearestEntry

    printStringRange(strings);
}

