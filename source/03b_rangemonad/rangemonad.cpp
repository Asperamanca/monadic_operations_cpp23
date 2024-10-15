#include "rangemonad.h"
#include <algorithm>
#include <ranges>

void CRangeMonad::compileAll(const std::vector<CProject>& projects)
{
    namespace vw = std::views;
    auto diagnostics = projects
                       | vw::transform(getFilesInProject) | vw::join
                       | vw::transform(compile)           | vw::join;
    std::ranges::for_each(diagnostics,printDiagnostic);
}

