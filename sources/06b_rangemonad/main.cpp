#include "rangemonad.h"
#include "../common/diagnosticinfo.h"

// Print all diagnostics from the files contained in multiple folders
// Range monadimplementation - compare to 06a_classicloop
int main(int argc, char* argv[])
{
    using namespace mop;

    CRangeMonad::compileAll(getTestProjects());

    // Shows a neat trick to see some informations about the functions of a pipeline
    CRangeMonad::printTypeTrick(getTestProjects());

    return 0;
}
