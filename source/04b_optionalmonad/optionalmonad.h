#ifndef OPTIONALMONAD_H
#define OPTIONALMONAD_H

#include "../common/elementdata.h"
#include "../common/printutils.h"
#include "../common/compilerinfo.h" // IWYU pragma: keep
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include <optional>




class COptionalMonad
{
private:
    static std::optional<CElement> getElement(const CElementDatabase& db, const ElementKey& key);
    static std::optional<CTableData> getTable(const CElement& element);
    static std::optional<CTableCell> getCell(const CTableData& tableData, const CCellLocation& location);
    static std::optional<int> getNumericCellValue(const CTableCell& cell);
    static bool isNegative(const int value);

    static std::optional<bool> isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);
    static std::optional<int> getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);
    static std::optional<std::strong_ordering> compare(const std::optional<int>& left, const std::optional<int>& right);

    static std::optional<bool> isNumericTableCellValueNegativeWithIfs(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);

    template<class TRet>
    static std::optional<TRet> log();
public:
    static std::optional<bool> isAnyTrendValueNegative(const CElementDatabase& db, const ElementKey& key);

    static void testForNegativeNumericValue();
    static void testForValueComparison();
};


template<class TRet>
std::optional<TRet> COptionalMonad::log()
{
    printlnWrapper("Error:");
#ifdef SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif
    return std::nullopt;
}




void testMbindIdentity();


#endif // OPTIONALMONAD_H
