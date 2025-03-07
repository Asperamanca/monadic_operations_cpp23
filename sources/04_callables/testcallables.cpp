#include "testcallables.h"
#include "../common/printutils.h"
#include "../common/sharedfunctions.h"
#include <vector>
#include <ranges>
#include <functional>
#include <cmath>
#include <numbers>

namespace mop
{


double calculateAreaOverloaded(const double radius)
{
    return std::pow(radius, 2.0) * std::numbers::pi;
}

int calculateAreaOverloaded(const int radius)
{
    const auto radiusSquared = (radius * radius);
    // Approximation
    return (radiusSquared * 3) + (radiusSquared / 7);
}


double CConversions::calculateAreaStatic(const double radius)
{
    return std::pow(radius, 2.0) * std::numbers::pi;
}

std::string CConversions::formatOutputStatic(const double value)
{
    return std::format("{:}", value);
}

double CConversions::calculateAreaMember(const double radius)
{
    return std::pow(radius, 2.0) * std::numbers::pi;
}

std::string CConversions::formatOutputMember(const double value)
{
    return std::format("{:}", value);
}

double CCalculateArea::operator()(const double radius) const
{
    return std::pow(radius, 2.0) * std::numbers::pi;
}

std::string CFormatOutput::operator()(const double value) const
{
    return std::format("{:}",value);
}


double CValue::getValue() const
{
    return m_Value;
}

// Neat trick to see types at compile time, through deprecated warning
template <typename... Ts>
[[deprecated]] constexpr void printTypes(Ts&&...) {}

template<class T>
void printTypeName(T&& arg)
{
    printlnWrapper("Type name: {:}",typeid(T).name());
    static_assert(std::is_compound_v<T>);
    // You can try out various checks to see which callables have which type properties
    // static_assert(std::is_reference_v<T>);
    // static_assert(! std::is_pointer_v<std::remove_cvref_t<T>>);
    // static_assert(! std::is_function_v<std::remove_cvref_t<T>>);
    // static_assert(! std::is_member_pointer_v<T>);
    // static_assert(! std::is_class_v<T>);
}


void CTestCallables::_01_freeFunction()
{
    printlnWrapper("_01_freeFunction");
    printTypeName(calculateArea);

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform(calculateArea)
                   | std::views::transform(formatArea);
    printStringRange(viewOutput);
}

void CTestCallables::_01b_freeFunctionOverloaded()
{
    printlnWrapper("_01b_freeFunctionOverloaded");
    // Can't print typename of inline lambda because...it's inline

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform([](auto&& val){return calculateAreaOverloaded(val);})
                   | std::views::transform(formatArea);
    printStringRange(viewOutput);
}

void CTestCallables::_02_staticClassFunction()
{
    printlnWrapper("_02_staticClassFunction");
    printTypeName(CConversions::calculateAreaStatic);

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform(CConversions::calculateAreaStatic)
                   | std::views::transform(CConversions::formatOutputStatic);
    printStringRange(viewOutput);
}

void CTestCallables::_03_inlineLambda()
{
    printlnWrapper("_03_inlineLambda");
    // Can't print typename of inline lambda because...it's inline

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform([](const double& value){return value * value;})
                   | std::views::transform([](const double& value){return std::format("{:}",value);});
    printStringRange(viewOutput);
}

void CTestCallables::_04_inlineLambdaInjectParameters()
{
    const double power = 3.0;

    printlnWrapper("_04_inlineLambdaInjectParameters");
    // Can't print typename of inline lambda because...it's inline

    auto vecInput = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecInput
                   | std::views::transform([power](const double& value){return std::pow(value, power);})
                   | std::views::transform([](const double& value){return std::format("{:}",value);});
    printStringRange(viewOutput);
}

void CTestCallables::_05_bindBackInjectParameter()
{
#ifdef MOP_SUPPORTS_BIND_BACK
    const double power = 3.0;

    printlnWrapper("_05_bindBackInjectParameter");
    printTypeName(std::bind_back(std::pow<double,double>,power));

    auto vecInput = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecInput
                   | std::views::transform(std::bind_back(std::pow<double,double>,power))
                   | std::views::transform([](const double& value){return std::format("{:}",value);});
    printStringRange(viewOutput);
#else
    printlnWrapper("Your compiler does not support bind_back");
#endif
}

void CTestCallables::_06_memFnMemberFunctionObj()
{
    printlnWrapper("_06_memFnMemberFunctionObj");
    printTypeName(std::mem_fn(&CValue::getValue));

    auto vecRadiiObj = std::vector{CValue{1.5},CValue{2.0},CValue{2.5}};
    auto viewOutput = vecRadiiObj
                    | std::views::transform(std::mem_fn(&CValue::getValue))
                    | std::views::transform(calculateArea)
                    | std::views::transform(formatArea);
    printStringRange(viewOutput);
}

void CTestCallables::_07_inlineLambdaMemberFunctionObj()
{
    printlnWrapper("_07_inlineLambdaMemberFunctionObj");
    // Can't print typename of inline lambda because...it's inline

    auto vecRadiiObj = std::vector{CValue{1.5},CValue{2.0},CValue{2.5}};
    auto viewOutput = vecRadiiObj
                   | std::views::transform([](const CValue& obj){return obj.getValue();})
                   | std::views::transform(calculateArea)
                   | std::views::transform(formatArea);
    printStringRange(viewOutput);
}

void CTestCallables::_08_bindMemberFunctionParam()
{
    CConversions conv;

    printlnWrapper("_08_bindMemberFunctionParam");
    printTypeName(std::bind_front(&CConversions::calculateAreaMember, &conv));

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform(std::bind_front(&CConversions::calculateAreaMember, &conv))
                   | std::views::transform(std::bind_front(&CConversions::formatOutputMember, &conv));
    printStringRange(viewOutput);
}

void CTestCallables::_09_inlineLambdaMemberFunctionParam()
{
    CConversions conv;

    printlnWrapper("_09_inlineLambdaMemberFunctionParam");
    // Can't print typename of inline lambda because...it's inline

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform([&conv](const double& value){return conv.calculateAreaMember(value);})
                   | std::views::transform([&conv](const double& value){return conv.formatOutputMember(value);});
    printStringRange(viewOutput);
}

void CTestCallables::_10_namedLambda()
{
    auto calculateAreaLocalLambda = [](const double radius)
    {
        return std::pow(radius, 2.0) * std::numbers::pi;
    };

    auto formatOutputLocalLambda = [](const double value)
    {
        return std::format("{:}",value);
    };

    printlnWrapper("_10_namedLambda");
    printTypeName(calculateAreaLocalLambda);


    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform(calculateAreaLocalLambda)
                   | std::views::transform(formatOutputLocalLambda);
    printStringRange(viewOutput);
}

void CTestCallables::_11_functionObject()
{
    CCalculateArea calculateAreaFunctionObject;
    CFormatOutput formatOutputFunctionObject;

    printlnWrapper("_11_functionObject");
    printTypeName(calculateAreaFunctionObject);

    auto vecRadii = std::vector{1.5,2.0,2.5};
    auto viewOutput = vecRadii
                   | std::views::transform(calculateAreaFunctionObject)
                   | std::views::transform(formatOutputFunctionObject);
    printStringRange(viewOutput);
}

void CTestCallables::_12_stdFunction()
{
    auto vecRadii = std::vector{1.5,2.0,2.5};

    // std::function from free functions
    {
        std::function<double(double)> fCalculateArea = calculateArea;
        std::function<std::string(double)> fFormatOutput = formatArea;

        printlnWrapper("_12_stdFunction_freeFunction");
        printTypeName(fCalculateArea);

        // Function could be a passed parameter, adding flexibility
        auto viewOutput = vecRadii
                       | std::views::transform(fCalculateArea)
                       | std::views::transform(fFormatOutput);
        printStringRange(viewOutput);
    }

    // std::function from static functions
    {
        std::function<double(double)> fCalculateArea = CConversions::calculateAreaStatic;
        std::function<std::string(double)> fFormatOutput = CConversions::formatOutputStatic;

        printlnWrapper("_12_stdFunction_staticFunction");
        printTypeName(fCalculateArea);

        // Function could be a passed parameter, adding flexibility
        auto viewOutput = vecRadii
                       | std::views::transform(fCalculateArea)
                       | std::views::transform(fFormatOutput);
        printStringRange(viewOutput);
    }

    // std::function from inline lambda
    {
        std::function<double(double)> fCalculateArea = [](const double& value){return value * value;};
        std::function<std::string(double)> fFormatOutput = [](const double& value){return std::format("{:}",value);};

        printlnWrapper("_12_stdFunction_inlineLambda");
        printTypeName(fCalculateArea);

        // Function could be a passed parameter, adding flexibility
        auto viewOutput = vecRadii
                       | std::views::transform(fCalculateArea)
                       | std::views::transform(fFormatOutput);
        printStringRange(viewOutput);
    }

    //...and so on, and so forth
}

template<class TFirst, class TSecond>
    requires std::is_invocable_v<TFirst,double> && std::is_same_v<double, std::invoke_result_t<TFirst,double>> &&
             std::is_invocable_v<TSecond,double>    && std::is_same_v<std::string, std::invoke_result_t<TSecond,double>>
auto getStringsViaTemplateInvokables(const std::vector<double>& v, TFirst&& fFirst, TSecond&& fSecond)
{
    printTypeName(fFirst);

    return  v
            | std::views::transform(std::forward<TFirst>(fFirst))
            | std::views::transform(std::forward<TSecond>(fSecond));
}

void CTestCallables::_13_templateInvokable()
{
    auto v = std::vector{1.5,2.0,2.5};
    // With free functions
    {
        printlnWrapper("_13_templateInvokable_freeFunction");

        auto strings = getStringsViaTemplateInvokables(v,calculateArea,formatArea);
        printStringRange(strings);
    }

    // With static functions
    {
        printlnWrapper("_13_templateInvokable_staticFunction");

        auto strings = getStringsViaTemplateInvokables(v,CConversions::calculateAreaStatic,CConversions::formatOutputStatic);
        printStringRange(strings);
    }

    // With inline lambda
    {
        printlnWrapper("_13_templateInvokable_inlineLambda");

        auto strings = getStringsViaTemplateInvokables(v,
                                                       [](const double& radius){return std::pow(radius, 2.0) * std::numbers::pi;},
                                                       [](const double& value){return std::format("{:}",value);});
        printStringRange(strings);
    }
    //...and so on, and so forth
}

} // namespace mop

