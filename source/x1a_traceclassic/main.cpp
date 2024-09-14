
#include "../common/noisy.h"

// Shows constructor/destructor calls when passing an object by reference, then overwriting it
// Compare to "tracervo" example

void foo(const int value, CNoisy& result)
{
    result=CNoisy(value);
    return;
}

int main(int argc, char* argv[])
{
    CNoisy result;
    foo(5,result);
    return 0;
}


