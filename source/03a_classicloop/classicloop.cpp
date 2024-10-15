#include "classicloop.h"

void CClassicLoop::compileAll(const std::vector<CProject>& projects)
{
    for(const auto& project : projects)
    {
        auto files = getFilesInProject(project);

        for(const auto& file : files)
        {
            auto diagnostics = compile(file);
            for(const auto& diagnostic : diagnostics)
            {
                printDiagnostic(diagnostic);
            }
        }
    }
}
