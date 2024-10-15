#include "classicloop.h"

void CClassicLoop::compileAll(const std::vector<CProject>& folders)
{
    for(const auto& folder : folders)
    {
        auto files = getFilesInProject(folder);

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
