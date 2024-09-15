#include "diagnosticinfo.h"
#include "../common/printutils.h"


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

std::vector<CFile> getFilesInFolder(const CFolder& input)
{
    // Use for tracing:
    //printlnWrapper("Called getFilesInFolder with {:}",input.m_FolderPath);

    if (input.m_FolderPath.empty())
    {
        return {};
    }
    // Let's fake it with test data
    return getTestFiles(input.m_FolderPath);
}

// Functions that provide dummy test data

std::vector<CFolder> getTestFolders()
{
    return {{CFolder{.m_FolderPath = "c:/dev/proj"}},
            {CFolder{.m_FolderPath = "c:/dev/fooproj"}},
            {CFolder{.m_FolderPath = "c:/dev/barproj"}}};
}

std::vector<CFile> getTestFiles(const std::string& folderPath)
{
    return std::vector<CFile>{{.m_FilePath=std::format("{:}/x.cpp",folderPath)},
                              {.m_FilePath=std::format("{:}/y.cpp",folderPath)},
                              {.m_FilePath=std::format("{:}/z.cpp",folderPath)}};
}
