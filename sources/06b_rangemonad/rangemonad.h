#ifndef RANGEMONAD_H
#define RANGEMONAD_H

#include <vector>
#include "../common/diagnosticinfo.h"

namespace mop
{

class CRangeMonad
{
public:
    static void compileAll(const std::vector<CProject>& projects);

    // Illustration of traceCall trick
    static void traceCallTrick(const std::vector<CProject>& projects);
    static void printTypeTrick(const std::vector<CProject>& projects);
private:
    // Illustration of compiler errors
    static void compilerErrorFunctionReturnsWrongValueType();
    static void compilerErrorFunctionArgumentTypeMismatch();
    static void compilerErrorFunctionOverloadResolution();
    static void compilerErrorFunctionUnnecessaryJoin();
    static void compilerErrorFunctionMissingJoin();
    static void compilerErrorFunctionConstFilterView();
};

} // namespace mop

#endif // RANGEMONAD_H
