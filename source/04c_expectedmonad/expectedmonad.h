#ifndef EXPECTEDMONAD_H
#define EXPECTEDMONAD_H

#include "../common/elementdata.h"
#include "../common/utils.h"
#include "../common/printutils.h"
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include <expected>



class CExpectedMonad
{
private:
    static std::expected<CElement,CErrorInfo> getElement(const CElementDatabase& db, const ElementKey& key);

    static std::expected<CTableData,CErrorInfo> getTable(const CElement& element);
    static std::expected<CTableCell,CErrorInfo> getCell(const CTableData& tableData, const CCellLocation& location);
    static std::expected<int,CErrorInfo> getNumericCellValue(const CTableCell& cell);
    static bool isNegative(const int value);

    static std::expected<bool,CErrorInfo> isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);
    static std::expected<int,CErrorInfo> getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);
    template<class TValue>
    static std::expected<std::strong_ordering, CErrorInfo> compare(const std::expected<TValue, CErrorInfo>& left, const std::expected<TValue, CErrorInfo>& right);

    template<class TRet>
    static std::expected<TRet,CErrorInfo> log(const CErrorInfo& errorInfo);
public:

    static void testForNegativeNumericValue();
    static void testForValueComparison();
};

template<class TValue>
std::expected<std::strong_ordering, CErrorInfo> CExpectedMonad::compare(const std::expected<TValue, CErrorInfo>& left, const std::expected<TValue, CErrorInfo>& right)
{
    if ( ! left.has_value())
    {
        return std::unexpected(left.error());
    }

    if ( ! right.has_value())
    {
        return std::unexpected(right.error());
    }

    return left.value() <=> right.value();
}

template<class TRet>
std::expected<TRet, CErrorInfo> CExpectedMonad::log(const CErrorInfo& errorInfo)
{
    printlnWrapper("Error: {:}", errorInfo.m_Message);
#ifdef SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif
    return std::unexpected{errorInfo};
}

#endif // EXPECTEDMONAD_H
