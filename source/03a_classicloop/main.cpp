#include "classicloop.h"


// Print all diagnostics from the files contained in multiple folders
// Classic loop implementation - compare to 03b_rangemonad
int main(int argc, char* argv[])
{
    CClassicLoop::compileAll(getTestFolders());

    return 0;
}
