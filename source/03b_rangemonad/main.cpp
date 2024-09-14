#include "rangemonad.h"
#include "../common/diagnosticinfo.h"

int main(int argc, char* argv[])
{
    CRangeMonad::compileAll(getTestFolders());

    return 0;
}
