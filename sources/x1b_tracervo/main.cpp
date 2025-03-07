
#include "../common/noisy.h"

// Shows constructor/destructor calls when simply returning an object
// Return value optimization / Copy elision prevents extra constructor calls
//  See https://en.cppreference.com/w/cpp/language/copy_elision
// Note that this could break code if you depend on side effects in the constructors!
// Compare to "traceclassic" example

namespace mop
{

CNoisy foo(const int value)
{
    int x = value;
    return x;
}

} // namespace mop

int main(int argc, char* argv[])
{
    using namespace mop;
    auto x = foo(5);
    return 0;
}
