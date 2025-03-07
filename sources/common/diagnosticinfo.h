#ifndef DIAGNOSTICINFO_H
#define DIAGNOSTICINFO_H

#include <string>
#include <vector>
#include "../common/noisy.h" // IWYU pragma: keep

// Shared file for example 01 (Functor section)

namespace mop
{

class CFile // : public CNoisy // Enable to see constructor/destructor calls
{
public:
    std::string m_FilePath{};
};

class CProject // : public CNoisy  // Enable to see constructor/destructor calls
{
public:
    std::vector<CFile> m_SourceFiles;
};


enum class EDiagnosticType : int
{
    None = 0,
    Warning,
    Error
};

class CDiagnosic // : public CNoisy // Enable to see constructor/destructor calls
{
public:
    static CDiagnosic createError(const CFile& file, const std::string& message);
    static CDiagnosic createWarning(const CFile& file, const std::string& message);
public:
    CFile m_File;
    EDiagnosticType m_eType{};
    std::string m_Message;
};

void printDiagnostic(const CDiagnosic& info);
std::vector<CDiagnosic> compile(const CFile& input);
std::vector<CFile> getFilesInProject(const CProject& input);

std::vector<CProject> getTestProjects();

} // namespace mop

#endif // DIAGNOSTICINFO_H
