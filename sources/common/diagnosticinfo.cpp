#include "diagnosticinfo.h"
#include "../common/printutils.h"

namespace mop
{

CDiagnosic CDiagnosic::createError(const CFile& file, const std::string& message)
{
    return {.m_File = file, .m_eType = EDiagnosticType::Error, .m_Message  = message};
}

CDiagnosic CDiagnosic::createWarning(const CFile& file, const std::string& message)
{
    return {.m_File = file, .m_eType = EDiagnosticType::Warning, .m_Message  = message};
}

void printDiagnostic(const CDiagnosic& info)
{
    // Use for tracing:
    //printlnWrapper("Called printDiagnostic for {:}",info.m_File.m_FilePath);

    auto fGetTypeString = [](const EDiagnosticType& eType) -> std::string
    {
        switch (eType)
        {
            using enum EDiagnosticType;
            case Warning:   return {"Warning"};
            case Error:     return {"Error"};
            case None:      break;
        }
        return {"None"};
    };

    printlnWrapper( "File: {:} Type: {:} Message: {:}",
                 info.m_File.m_FilePath,
                 fGetTypeString(info.m_eType),
                 info.m_Message);
}

std::vector<CDiagnosic> compile(const CFile& input)
{
    // Use for tracing:
    //printlnWrapper("Called compile with {:}",input.m_FilePath);

    if (input.m_FilePath.empty())
    {
        return {};
    }
    // Let's fake it: Every file creates 2 diagnostics
    return std::vector<CDiagnosic>{CDiagnosic::createError(input, "Some error"),
                                   CDiagnosic::createWarning(input, "Some warning")};
}

std::vector<CFile> getFilesInProject(const CProject& input)
{
    // Use for tracing:
    //printlnWrapper("Called getFilesInProject with {:}",input.m_ProjectFile);

    if (input.m_SourceFiles.empty())
    {
        return {};
    }
    return input.m_SourceFiles;
}

// Functions that provide dummy test data

std::vector<CProject> getTestProjects()
{
    return {{CProject{.m_SourceFiles = {CFile{"c:/dev/proj/x.cpp"},CFile{"c:/dev/proj/y.cpp"},CFile{"c:/dev/proj/z.cpp"}}}},
            {CProject{.m_SourceFiles = {CFile{"c:/dev/proj/test/t1.cpp"},CFile{"c:/dev/proj/test/t2.cpp"}}}},
            {CProject{.m_SourceFiles = {CFile{"c:/dev/proj/shared/common.cpp"}}}}};
}

} // namespace mop

