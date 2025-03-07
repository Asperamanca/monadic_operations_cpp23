#ifndef OPTIONALMONAD_H
#define OPTIONALMONAD_H

#include "../common/elementdata.h"
#include "../common/printutils.h"
#include "../common/compilerinfo.h" // IWYU pragma: keep
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include <optional>


namespace mop
{

// Just a wrapper around all the functions related to the optional monad example
class COptionalMonad
{
public:
    static std::optional<bool> isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);

private:
    static std::optional<CElement> getElement(const CElementDatabase& db, const ElementKey& key);
    static std::optional<CTableData> getTable(const CElement& element);
    static std::optional<CTableCell> getCell(const CTableData& tableData, const CCellLocation& location);
    static std::optional<int> getNumericCellValue(const CTableCell& cell);
    static bool isNegative(const int value);

    static std::optional<bool> isNumericTableCellValueNegativeWithIfs(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);

    template<class TRet>
    static std::optional<TRet> log();

private:
    // Illustration of compiler errors
    static void compilerErrorFunctionReturnsNonOptionalWhenItShould();
    static void compilerErrorFunctionReturnsWrongValueType();
    static void compilerErrorFunctionArgumentTypeMismatch();
    static void compilerErrorFunctionOverloadResolution();

public:
    static std::optional<bool> isAnyTrendValueNegative(const CElementDatabase& db, const ElementKey& key);
};


template<class TRet>
std::optional<TRet> COptionalMonad::log()
{
    printlnWrapper("Error:");
#ifdef MOP_SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif
    return std::nullopt;
}

} // namespace mop

#endif // OPTIONALMONAD_H
