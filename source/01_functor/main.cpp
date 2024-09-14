
#include "../common/printutils.h"
#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <format>
#include <cmath>

// Not the functor we are looking for...
class CNegator
{
public:
    int operator()(const int value) const
    {
        return -value;
    }
};


// Helper functions

std::string dblToStr(const double value)
{
    return std::format("{:}",value);
}

double makeSquared(const double value)
{
    return std::pow(value,2.0);
}

void _01_testDoublePowToStrClassic()
{
    auto v = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    for(const auto& value : v)
    {
        strings.push_back(std::format("{:}",std::pow(value,2.0)));
    }
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printOutput(strings);
}

void _02_testDoublePowToStrClassicWithFunctions()
{
    auto v = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    for(const auto& value : v)
    {
        strings.push_back(dblToStr(makeSquared(value)));
    }
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printOutput(strings);
}


void _03_testDoublePowToStrFunctorView()
{
    auto v = std::vector{1.5,2.0,2.5};

    auto strings =
        std::views::transform(std::views::transform(v,makeSquared),
                              dblToStr);
    // {"2.25", "4", "6.25"}

    // Print type name of view
    printlnWrapper("{:}",typeid(strings).name());

    // Print output for testing
    printOutput(strings);
}



void _04_testDoublePowToStrFunctorViewWithPipe()
{
    auto v = std::vector{1,2,5,8};

    auto strings = v
             | std::views::transform(makeSquared)
             | std::views::transform(dblToStr);
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printOutput(strings);
}


std::vector<std::string> _05_convertViewResultToContainer()
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

// Extra: Eager ranges algorithm
void _x1_testFunctorVectorDoublePowToStr()
{
    auto v = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    std::ranges::transform(v, std::back_inserter(strings),
                           [](const double value){return dblToStr(makeSquared(value));});
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printOutput(strings);
}


// Extra: Dangling reference
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

void _x2_testDanglingReference()
{
    using namespace std;
    auto v = vector{1,3,7};

    auto strings = v
                   | views::transform(getNearestEntry)
                   | views::transform(&CEntry::m_Text);

    printOutput(strings);
}

int main(int argc, char* argv[])
{
    // They all do the same thing:
    _01_testDoublePowToStrClassic();
    _02_testDoublePowToStrClassicWithFunctions();
    _03_testDoublePowToStrFunctorView();
    _04_testDoublePowToStrFunctorViewWithPipe();

    _x1_testFunctorVectorDoublePowToStr();
    // _x2_testDanglingReference();     // This will crash!

    return 0;
}


