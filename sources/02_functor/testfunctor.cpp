#include "testfunctor.h"
#include "functor.h"
#include "../common/printutils.h"
#include "../common/sharedfunctions.h"
#include <algorithm>
#include <ranges>
#include <optional>

namespace mop
{

// NOTE:
// calculateArea and formatArea are declared in ../common/sharedfunctions.h


// First: Classic, non-functor implementations

void intro01ClassicSingleValue()
{
    const double radius = 1.5;

    // Calculate a single value, plain and simple
    const auto result = formatArea(calculateArea(radius));

    printlnWrapper("Classic, single value {:}",result);
}

void intro02ClassicVector()
{
    const std::vector<double> vecRadii{1.5,2.5,3.0};

    // Add a loop for a vector
    // Straightforward, but notice how different the code looks
    //  from the single value version. Notice how the implementations
    //  using functors are pretty much identical in comparison
    std::vector<std::string> resultVec;
    for(const double& radius : vecRadii)
    {
        // Here at least, we can re-use the function we already have
        resultVec.push_back(formatArea(calculateArea(radius)));
    }

    printlnWrapper("Classic, vector");
    for(const auto& result : resultVec)
    {
        printlnWrapper("{:}",result);
    }
}

void intro03ClassicOptionalValue()
{
    const std::optional<double> oRadius = 1.5;

    // Add a check for empty optional
    // Again, notice how different this looks from the single value
    //  and vector cases
    std::optional<std::string> oResult;
    if (oRadius)
    {
        oResult = formatArea(calculateArea(oRadius.value()));;
    }

    printlnWrapper("Classic, optional value HasValue: {:} Value: {:}",oResult.has_value(), oResult.value_or(std::string{}));
}


// Second: Functor introduction (with lifted functions)


void intro11FunctorLiftSingleValue()
{
    const double radius = 1.5;

    // Stupid, because the functions can handle a single value, anyway
    // But it shows the mechanism, and you can see how the code becomes
    //  identical to the vector and optional cases
    auto calculateStupidArea = liftStupid<double>(calculateArea);
    auto formatStupidOutput = liftStupid<double>(formatArea);
    // Use the new functions
    const auto result = formatStupidOutput(calculateStupidArea(radius));

    printlnWrapper("FunctorFunction, single value {:}",result);
}

void intro12FunctorLiftVector()
{
    const std::vector<double> vecRadii{1.5,2.5,3.0};

    // Lift the existing functions so they can suddenly handle std::vector
    auto calculateVecArea = liftVector<double>(calculateArea);
    auto formatVecOutput = liftVector<double>(formatArea);
    // Now use the new functions
    const auto resultVec = formatVecOutput(calculateVecArea(vecRadii));

    printlnWrapper("FunctorFunction, vector");
    for(const auto& result : resultVec)
    {
        printlnWrapper("{:}",result);
    }
}

void intro13FunctorLiftOptionalValue()
{
    const std::optional<double> oRadius = 1.5;

    // Lift the existing functions so they can suddenly handle std::optional
    auto calculateOptionalArea = liftOptional<double>(calculateArea);
    auto formatOptionalOutput = liftOptional<double>(formatArea);
    // Now use the new functions
    const auto oResult = formatOptionalOutput(calculateOptionalArea(oRadius));

    printlnWrapper("FunctorFunction, optional value HasValue: {:} Value: {:}",oResult.has_value(), oResult.value_or(std::string{}));
}


// Third: Container-like functor wrapper object

void intro21FunctorWrapperSingleValue()
{
    const double radius = 1.5;

    // Stupid, because the functions can handle a single value, anyway
    // But it shows the mechanism, and you can see how the code becomes
    //  identical to the vector and optional cases
    const auto result =  CFunctorStupid{radius}.transform(calculateArea)
                       .transform(formatArea)
                       .result();

    printlnWrapper("FunctorWrapper, single value {:}",result);
}

void intro22FunctorWrapperVector()
{
    const std::vector<double> vecRadii{1.5,2.5,3.0};

    // Use a wrapper functor to transform our vector of values from
    //  radius -> area -> string
    const auto resultVec = CFunctorVec{vecRadii}
                            .transform(calculateArea)
                            .transform(formatArea)
                            .result();

    printlnWrapper("FunctorWrapper, vector");
    for(const auto& result : resultVec)
    {
        printlnWrapper("{:}",result);
    }
}


void intro23FunctorWrapperOptionalValue()
{
    const std::optional<double> oRadius = 1.5;

    // Use a wrapper functor to transform our optional value from
    //  radius -> area -> string
    const auto result = CFunctorOpt{oRadius}
                                .transform(calculateArea)
                                .transform(formatArea)
                                .result();

    printlnWrapper("FunctorWrapper, optional value HasValue: {:} Value: {:}",result.has_value(), result.value_or(std::string{}));
}


// A template function to implement our pipeline once, and once only
template<class TFunc, class TValue>
auto introFunctor_CalculateTemplate(TValue&& in)
{
    return TFunc{std::forward<TValue>(in)}.transform(calculateArea)
        .transform(formatArea)
        .result();
}

void intro31FunctorTemplateSingleValue()
{
    const double startValue = 1.5;
    const auto result = introFunctor_CalculateTemplate<CFunctorStupid<double>>(startValue);
    printlnWrapper("Functor, single value {:}",result);
}

void intro32FunctorTemplateVector()
{
    const std::vector<double> startValue{1.5,2.5,3.0};
    const auto resultVec = introFunctor_CalculateTemplate<CFunctorVec<double>>(startValue);
    printlnWrapper("Functor, vector");
    for(const auto& result : resultVec)
    {
        printlnWrapper("{:}",result);
    }
}

void intro33FunctorTemplateOptionalValue()
{
    const std::optional<double> startValue = 1.5;
    const auto result = introFunctor_CalculateTemplate<CFunctorOpt<double>>(startValue);
    printlnWrapper("Functor, optional value HasValue: {:} Value: {:}",result.has_value(), result.value_or(std::string{}));
}



void intro41FunctorShowComposition()
{
    const auto vecRadius = std::vector{2.25,5.0,10.0};

    // 1: Create result using two transformations
    auto functor2Transforms = CFunctorVec(vecRadius)
                                .transform(calculateArea)
                                .transform(formatArea);

    // 2: Create result using a composition of both functions
    auto functorComposed = CFunctorVec(vecRadius)
                               .transform([](const double& radius)
                                          { return formatArea(calculateArea(radius)); });

    const bool bFunctorsEqual = (functor2Transforms.result() == functorComposed.result());
    printlnWrapper("Is the result of composition equal to separate transformations? {:}",bFunctorsEqual);
}

void intro42FunctorShowIdentity()
{
    const auto vecRadius = std::vector{2.25,5.0,10.0};
    auto functorWithIdentity = CFunctorVec(vecRadius)
                                   .transform(std::identity{});

    const bool bResultsUnchanged = (vecRadius == functorWithIdentity.result());
    printlnWrapper("Is the result of identity transformation equal to original data? {:}",bResultsUnchanged);
}

// // Ranges views example

void introRanges01Classic()
{
    auto radii = std::vector{1.5,2.0,2.5};

    std::vector<std::string> strings;
    for(const double& radius : radii)
    {
        // Here at least, we can re-use the function we already have
        strings.push_back(formatArea(calculateArea(radius)));
    }

    // {"2.25", "4", "6.25"}

    // Print output for testing
    printStringRange(strings);
}


void introRanges02FunctorView()
{
    auto radii = std::vector{1.5,2.0,2.5};

    auto strings =
        std::views::transform(std::views::transform(radii,calculateArea),
                              formatArea);
    // {"2.25", "4", "6.25"}

    // Print type name of view
    printlnWrapper("{:}",typeid(strings).name());

    // Print output for testing
    printStringRange(strings);
}



void introRanges03FunctorViewWithPipe()
{
    auto radii = std::vector{1,2,5,8};

    auto strings = radii
                   | std::views::transform(calculateArea)
                   | std::views::transform(formatArea);
    // {"2.25", "4", "6.25"}

    // Print output for testing
    printStringRange(strings);
}

std::vector<std::string> introRanges05ConvertViewResultToContainer()
{
    using namespace std;
    auto v = vector{1.5,2.0,2.5};

    auto strings = v
                   | views::transform(calculateArea)
                   | views::transform(formatArea);

#ifdef MOP_SUPPORTS_RANGES_TO
    return ranges::to<vector<string>>(strings);
#else
    return {strings.begin(), strings.end()};
#endif
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

void extra1_DanglingReference()
{
    using namespace std;
    auto v = vector{1,3,7};

    auto strings = v
                   | views::transform(getNearestEntry)
                   | views::transform(&CEntry::m_Text); // Obtain reference to a temporary - the return value of getNearestEntry

    printStringRange(strings);
}

} // namespace mop

