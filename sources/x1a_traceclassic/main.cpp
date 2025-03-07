
#include "../common/noisy.h"

// Shows constructor/destructor calls when passing an object by reference, then overwriting it
// Compare to "tracervo" example

namespace mop
{

void foo(const int value, CNoisy& result)
{
    result=CNoisy(value);
    return;
}

} // namespace mop

int main(int argc, char* argv[])
{
    using namespace mop;
    CNoisy result;
    foo(5,result);
    return 0;
}


