#include "rangemonad.h"
#include <algorithm>
#include <ranges>

void CRangeMonad::compileAll(const std::vector<CFolder>& folders)
{
    namespace vw = std::views;
    auto diagnostics = folders
                       | vw::transform(getFilesInFolder) | vw::join
                       | vw::transform(compile)          | vw::join;
    std::ranges::for_each(diagnostics,printDiagnostic);
}

