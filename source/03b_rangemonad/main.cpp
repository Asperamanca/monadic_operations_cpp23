#include "rangemonad.h"
#include "../common/diagnosticinfo.h"

// Print all diagnostics from the files contained in multiple folders
// Range monadimplementation - compare to 03a_classicloop
int main(int argc, char* argv[])
{
    CRangeMonad::compileAll(getTestFolders());

    return 0;
}
