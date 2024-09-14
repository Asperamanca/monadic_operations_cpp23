
#include "testcallables.h"

int main(int argc, char* argv[])
{
    CTestCallables::_01_freeFunction();
    CTestCallables::_02_staticClassFunction();
    CTestCallables::_03_inlineLambda();
    CTestCallables::_04_inlineLambdaInjectParameters();
    CTestCallables::_05_bindBackInjectParameter();
    CTestCallables::_06_memFnMemberFunctionObj();
    CTestCallables::_07_inlineLambdaMemberFunctionObj();
    CTestCallables::_08_bindMemberFunctionParam();
    CTestCallables::_09_inlineLambdaMemberFunctionParam();
    CTestCallables::_10_namedLambda();
    CTestCallables::_11_functionObject();
    CTestCallables::_12_stdFunction();
    CTestCallables::_13_templateInvokable();

    return 0;
}


