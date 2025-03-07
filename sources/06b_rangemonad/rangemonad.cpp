#include "rangemonad.h"
#include <algorithm>
#include <ranges>
#include "../common/utils.h"

namespace mop
{

void CRangeMonad::compileAll(const std::vector<CProject>& projects)
{
    namespace vw = std::views;
    auto diagnostics = projects
                       | vw::transform(getFilesInProject) | vw::join
                       | vw::transform(compile)           | vw::join;
    std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::traceCallTrick(const std::vector<CProject>& projects)
{
    // We can see the argument and return types of our function nicely using compiler warnings
    namespace vw = std::views;
    auto diagnostics = projects
                       | vw::transform(tracedCall(getFilesInProject)) | vw::join
                       | vw::transform(tracedCall(compile))           | vw::join;
    std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::printTypeTrick(const std::vector<CProject>& projects)
{
    namespace vw = std::views;
    auto diagnostics = projects
                       | vw::transform(wrapPrintType(getFilesInProject)) | vw::join
                       | vw::transform(wrapPrintType(compile))           | vw::join;
    std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::compilerErrorFunctionReturnsWrongValueType()
{
    // // Values don't matter - it won't compile anyway
    // std::vector<CProject> projects{};

    // auto fGetFilesInProjectWrongReturnType = [](const CProject& input) -> std::vector<int>
    //     {
    //         return {};
    //     };

    // namespace vw = std::views;
    // auto diagnostics = projects
    //                    | vw::transform(fGetFilesInProjectWrongReturnType) | vw::join
    //                    | vw::transform(compile)           | vw::join;
    // std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::compilerErrorFunctionArgumentTypeMismatch()
{
    // // Values don't matter - it won't compile anyway
    // std::vector<CProject> projects{};

    // auto fGetFilesInProjectWrongArgumentType = [](const int input) -> std::vector<CFile>
    // {
    //     return {};
    // };

    // namespace vw = std::views;
    // auto diagnostics = projects
    //                    | vw::transform(fGetFilesInProjectWrongArgumentType) | vw::join
    //                    | vw::transform(compile)           | vw::join;
    // std::ranges::for_each(diagnostics,printDiagnostic);
}

std::vector<CFile> getFilesInProjectOverloaded(const CProject& input)
{
    return {};
}

std::vector<CFile> getFilesInProjectOverloaded(const int value)
{
    return {};
}

void CRangeMonad::compilerErrorFunctionOverloadResolution()
{
    // // Values don't matter - it won't compile anyway
    // std::vector<CProject> projects{};

    // namespace vw = std::views;
    // auto diagnostics = projects
    //                    | vw::transform(getFilesInProjectOverloaded) | vw::join
    //                    | vw::transform(compile)           | vw::join;
    // std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::compilerErrorFunctionUnnecessaryJoin()
{
    // // Values don't matter - it won't compile anyway
    // std::vector<CProject> projects{};

    // auto fGetFilesInProjectDoesNotReturnVector = [](const CProject& input) -> CFile
    //     {
    //         return {};
    //     };

    // namespace vw = std::views;
    // auto diagnostics = projects
    //                    | vw::transform(fGetFilesInProjectDoesNotReturnVector) | vw::join
    //                    | vw::transform(compile)           | vw::join;
    // std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::compilerErrorFunctionMissingJoin()
{
    // // Values don't matter - it won't compile anyway
    // std::vector<CProject> projects{};

    // namespace vw = std::views;
    // auto diagnostics = projects
    //                    | vw::transform(getFilesInProject) // missing join
    //                    | vw::transform(compile)           | vw::join;
    // std::ranges::for_each(diagnostics,printDiagnostic);
}

void CRangeMonad::compilerErrorFunctionConstFilterView()
{
    // std::vector<CProject> projects{};

    // auto fIsFileValid = [](const CFile& file){return  ! file.m_FilePath.empty();};

    // namespace vw = std::views;
    // const auto files= projects  // Remove const and it works
    //                    | vw::transform(getFilesInProject) | vw::join
    //                    | vw::filter(fIsFileValid);

    // auto diagnostics = files | vw::transform(compile)           | vw::join;

    // std::ranges::for_each(diagnostics,printDiagnostic);
}

} // namespace mop

