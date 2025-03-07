#include "classicloop.h"


// Print all diagnostics from the files contained in multiple folders
// Classic loop implementation - compare to 06b_rangemonad
int main(int argc, char* argv[])
{
    using namespace mop;

    CClassicLoop::compileAll(getTestProjects());

    return 0;
}

