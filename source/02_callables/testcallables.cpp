#include "testcallables.h"
#include "../common/printutils.h"
#include <vector>
#include <ranges>
#include <functional>
#include <cmath>


std::string dblToStr(const double value)
{
    return std::format("{:}", value);
}

double makeSquared(const double value)
{
    return std::pow(value, 2.0);
}

double makeSquaredOverloaded(const double value)
{
    return std::pow(value, 2.0);
}

int makeSquaredOverloaded(const int value)
{
    return value*value;
}


double CConversions::makeSquaredStatic(const double value)
{
    return std::pow(value, 2.0);
}

std::string CConversions::dblToStrStatic(const double value)
{
    return std::format("{:}", value);
}

double CConversions::makeSquaredMember(const double value)
{
    return std::pow(value, 2.0);
}

std::string CConversions::dblToStrMember(const double value)
{
    return std::format("{:}", value);
}

// static auto makeSquaredGlobalLambda = [](const double value)
// {
//     return std::pow(value,2.0);
// };

// static auto dblToStrGlobalLambda = [](const double value)
// {
//     return std::format("{:}",value);
// };

double CMakeSquared::operator()(const double value) const
{
    return std::pow(value,2.0);
}

std::string CDblToStr::operator()(const double value) const
{
    return std::format("{:}",value);
}


double CValue::getValue() const
{
    return m_Value;
}




void CTestCallables::_01_freeFunction()
{
    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform(makeSquared)
                   | std::views::transform(dblToStr);
    printStringRange(strings);
}

void CTestCallables::_01b_freeFunctionOverloaded()
{
    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform([](auto&& val){return makeSquaredOverloaded(val);})
                   | std::views::transform(dblToStr);
    printStringRange(strings);
}

void CTestCallables::_02_staticClassFunction()
{
    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform(CConversions::makeSquaredStatic)
                   | std::views::transform(CConversions::dblToStrStatic);
    printStringRange(strings);
}

void CTestCallables::_03_inlineLambda()
{
    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform([](const double& value){return value * value;})
                   | std::views::transform([](const double& value){return std::format("{:}",value);});
    printStringRange(strings);
}

void CTestCallables::_04_inlineLambdaInjectParameters()
{
    const double power = 2.0;

    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform([power](const double& value){return std::pow(value, power);})
                   | std::views::transform([](const double& value){return std::format("{:}",value);});
    printStringRange(strings);
}

void CTestCallables::_05_bindBackInjectParameter()
{
#ifdef SUPPORTS_BIND_BACK
    const double power = 2.0;

    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform(std::bind_back(std::pow<double,double>,power))
                   | std::views::transform([](const double& value){return std::format("{:}",value);});
    printStringRange(strings);
#else
    printlnWrapper("Your compiler does not support bind_back");
#endif
}

void CTestCallables::_06_memFnMemberFunctionObj()
{
    auto vObj = std::vector{CValue{1.5},CValue{2.0},CValue{2.5}};
    auto strings = vObj
                    | std::views::transform(std::mem_fn(&CValue::getValue))
                    | std::views::transform(makeSquared)
                    | std::views::transform(dblToStr);
    printStringRange(strings);
}

void CTestCallables::_07_inlineLambdaMemberFunctionObj()
{
    auto vObj = std::vector{CValue{1.5},CValue{2.0},CValue{2.5}};
    auto strings = vObj
                   | std::views::transform([](const CValue& obj){return obj.getValue();})
                   | std::views::transform(makeSquared)
                   | std::views::transform(dblToStr);
    printStringRange(strings);
}

void CTestCallables::_08_bindMemberFunctionParam()
{
    CConversions conv;

    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform(std::bind_front(&CConversions::makeSquaredMember, &conv))
                   | std::views::transform(std::bind_front(&CConversions::dblToStrMember, &conv));
    printStringRange(strings);
}

void CTestCallables::_09_inlineLambdaMemberFunctionParam()
{
    CConversions conv;

    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform([&conv](const double& value){return conv.makeSquaredMember(value);})
                   | std::views::transform([&conv](const double& value){return conv.dblToStrMember(value);});
    printStringRange(strings);
}

void CTestCallables::_10_namedLambda()
{
    auto makeSquaredLocalLambda = [](const double value)
    {
        return std::pow(value,2.0);
    };

    auto dblToStrLocalLambda = [](const double value)
    {
        return std::format("{:}",value);
    };

    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform(makeSquaredLocalLambda)
                   | std::views::transform(dblToStrLocalLambda);
    printStringRange(strings);
}

void CTestCallables::_11_functionObject()
{
    CMakeSquared makeSquaredFunctionObject;
    CDblToStr dblToStrFunctionObject;

    auto v = std::vector{1.5,2.0,2.5};
    auto strings = v
                   | std::views::transform(makeSquaredFunctionObject)
                   | std::views::transform(dblToStrFunctionObject);
    printStringRange(strings);
}

void CTestCallables::_12_stdFunction()
{
    auto v = std::vector{1.5,2.0,2.5};

    // std::function from free functions
    {
        std::function<double(double)> fMakeSquared = makeSquared;
        std::function<std::string(double)> fDblToStr = dblToStr;

        // Function could be a passed parameter, adding flexibility
        auto strings = v
                       | std::views::transform(fMakeSquared)
                       | std::views::transform(fDblToStr);
        printStringRange(strings);
    }

    // std::function from static functions
    {
        std::function<double(double)> fMakeSquared = CConversions::makeSquaredStatic;
        std::function<std::string(double)> fDblToStr = CConversions::dblToStrStatic;

        // Function could be a passed parameter, adding flexibility
        auto strings = v
                       | std::views::transform(fMakeSquared)
                       | std::views::transform(fDblToStr);
        printStringRange(strings);
    }

    // std::function from inline lambda
    {
        std::function<double(double)> fMakeSquared = [](const double& value){return value * value;};
        std::function<std::string(double)> fDblToStr = [](const double& value){return std::format("{:}",value);};

        // Function could be a passed parameter, adding flexibility
        auto strings = v
                       | std::views::transform(fMakeSquared)
                       | std::views::transform(fDblToStr);
        printStringRange(strings);
    }

    //...and so on, and so forth
}

template<class TMakeSquared, class TDblToStr>
    requires std::is_invocable_v<TMakeSquared,double> && std::is_invocable_v<TDblToStr,double>
auto getStringsViaTemplateInvokables(const std::vector<double>& v, const TMakeSquared& fMakeSquared, const TDblToStr& fDblToStr)
{
    return  v
            | std::views::transform(fMakeSquared)
            | std::views::transform(fDblToStr);
}

void CTestCallables::_13_templateInvokable()
{
    auto v = std::vector{1.5,2.0,2.5};
    // With free functions
    {
        auto strings = getStringsViaTemplateInvokables(v,makeSquared,dblToStr);
        printStringRange(strings);
    }

    // With static functions
    {
        auto strings = getStringsViaTemplateInvokables(v,CConversions::makeSquaredStatic,CConversions::dblToStrStatic);
        printStringRange(strings);
    }

    // With inline lambda
    {
        auto strings = getStringsViaTemplateInvokables(v,
                                                       [](const double& value){return value * value;},
                                                       [](const double& value){return std::format("{:}",value);});
        printStringRange(strings);
    }
    //...and so on, and so forth
}


