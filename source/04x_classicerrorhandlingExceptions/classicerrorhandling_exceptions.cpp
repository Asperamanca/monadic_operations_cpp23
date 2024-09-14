#include "classicerrorhandling_exceptions.h"
#include "../common/printutils.h"
#include "../common/stacktraceutils.h" // IWYU pragma: keep

CElement CClassicErrorHandlingExceptions::getElement(const CElementDatabase& db, const ElementKey& key)
{
    const auto iter = db.find(key);
    if (iter == db.cend())
    {
        throw std::out_of_range("Element not found");
    }
    return iter->second;
}

CTableData CClassicErrorHandlingExceptions::getTable(const CElement& element)
{
    return getTypeData<CTableData>(element);
}

CTableCell CClassicErrorHandlingExceptions::getCell(const CTableData& tableData, const CCellLocation& location)
{
    if ( (location.m_Column >= tableData.m_Size.m_ColumnCount) ||
        (location.m_Row >= tableData.m_Size.m_RowCount ))
    {
        throw std::out_of_range("Cell index invalid");
    }
    const auto index = location.m_Column+(location.m_Row*tableData.m_Size.m_ColumnCount);
    return tableData.m_Cells[index];
}

int CClassicErrorHandlingExceptions::getNumericCellValue(const CTableCell& cell)
{
    // Throws exception on type mismatch
    return std::get<int>(cell.m_CellValue);
}

void CClassicErrorHandlingExceptions::log(const std::string& message)
{
    printlnWrapper("Error: {:}", message);

#ifdef SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif
}

std::optional<std::strong_ordering> CClassicErrorHandlingExceptions::compare(const std::optional<int>& left, const std::optional<int>& right)
{
    if ( ! (left.has_value() && right.has_value()))
    {
        return {};
    }

    return *left <=> *right;
}

int CClassicErrorHandlingExceptions::getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    return getNumericCellValue(
                getCell(
                        getTable(getElement(db,key)),
                        cellLocation
                )
           );
}

bool CClassicErrorHandlingExceptions::getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    auto table = getTable(getElement(db,key));
    auto cell = getCell(table, cellLocation);
    return (getNumericCellValue(cell) < 0);
}

void CClassicErrorHandlingExceptions::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        auto oResult = tryCall(CClassicErrorHandlingExceptions::getNumericTableValueNegative,db,ElementKey(10),CCellLocation{.m_Column=1, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(),oResult.value_or(false));
    }

    // NOK Case
    {
        auto oResult = tryCall(CClassicErrorHandlingExceptions::getNumericTableValueNegative,db,10,CCellLocation{.m_Column=2, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(),oResult.value_or(false));
    }
}

void CClassicErrorHandlingExceptions::testForValueComparison()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        auto oValue1 = tryCall(CClassicErrorHandlingExceptions::getNumericTableCellValue,db,ElementKey(10),CCellLocation{.m_Column=0, .m_Row=1});
        auto oValue2 = tryCall(CClassicErrorHandlingExceptions::getNumericTableCellValue,db,ElementKey(30),CCellLocation{.m_Column=1, .m_Row=0});
        auto oCmp = compare(oValue1, oValue2);
        printlnWrapper("Ok: {:} Result: {:}", oCmp.has_value(),convStr(oCmp.value_or(std::strong_ordering::equal)));
    }

    // NOK Case
    {
        auto oValue1 = tryCall(CClassicErrorHandlingExceptions::getNumericTableCellValue,db,ElementKey(10),CCellLocation{.m_Column=0, .m_Row=1});
        auto oValue2 = tryCall(CClassicErrorHandlingExceptions::getNumericTableCellValue,db,ElementKey(30),CCellLocation{.m_Column=4, .m_Row=0});
        auto oCmp = compare(oValue1, oValue2);
        printlnWrapper("Ok: {:} Result: {:}", oCmp.has_value(),convStr(oCmp.value_or(std::strong_ordering::equal)));
    }
}
