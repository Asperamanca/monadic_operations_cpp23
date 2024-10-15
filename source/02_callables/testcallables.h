#ifndef TESTCALLABLES_H
#define TESTCALLABLES_H

#include <string>

std::string dblToStr(const double value);
double makeSquared(const double value);

class CConversions
{
public:
    static double makeSquaredStatic(const double value);
    static std::string dblToStrStatic(const double value);
    double makeSquaredMember(const double value);
    std::string dblToStrMember(const double value);
};

class CMakeSquared
{
public:
    double operator()(const double value) const;
};

class CDblToStr
{
public:
    std::string operator()(const double value) const;
};


struct CValue
{
    double getValue() const;

    double m_Value{};
};



class CTestCallables
{
public:
    static void _01_freeFunction();
    static void _01b_freeFunctionOverloaded();
    static void _02_staticClassFunction();
    static void _03_inlineLambda();
    static void _04_inlineLambdaInjectParameters();
    static void _05_bindBackInjectParameter();
    static void _06_memFnMemberFunctionObj();
    static void _07_inlineLambdaMemberFunctionObj();
    static void _08_bindMemberFunctionParam();
    static void _09_inlineLambdaMemberFunctionParam();
    static void _10_namedLambda();
    static void _11_functionObject();
    static void _12_stdFunction();
    static void _13_templateInvokable();

};

#endif // TESTCALLABLES_H
