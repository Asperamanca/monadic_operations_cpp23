#include "classicerrorhandling.h"
#include "../common/printutils.h"
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include <compare>

bool CClassicErrorHandling::getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation, bool& result)
{
    CElement element;
    if ( ! getElement(db, key, element))
    {
        return false;
    }

    CTableData table;
    if ( ! getTable(element, table))
    {
        return false;
    }

    CTableCell cell;
    if ( ! getCell(table, cellLocation, cell))
    {
        return false;
    }

    int value;
    if ( ! getNumericCellValue(cell, value))
    {
        return false;
    }

    result = (value < 0);
    return true;
}

void CClassicErrorHandling::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        bool bResult{};
        const bool bOk = CClassicErrorHandling::getNumericTableValueNegative(db,{10},{.m_Column=1, .m_Row=1}, bResult);
        printlnWrapper("Ok: {:} Result: {:}", bOk,bResult);
    }

    // NOK Case
    {
        bool bResult{};
        const bool bOk = CClassicErrorHandling::getNumericTableValueNegative(db,{10},{.m_Column=2, .m_Row=1}, bResult);
        printlnWrapper("Ok: {:} Result: {:}", bOk,bResult);
    }
}

void CClassicErrorHandling::testForValueComparison()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        int value1, value2;
        const bool bOk = CClassicErrorHandling::getNumericTableCellValue(db,{10},{.m_Column=0, .m_Row=1}, value1)
                         && CClassicErrorHandling::getNumericTableCellValue(db,{30},{.m_Column=1, .m_Row=0}, value2);
        std::strong_ordering cmp{std::strong_ordering::equal};
        if (bOk)
        {
            cmp = (value1 <=> value2);
        }
        printlnWrapper("Ok: {:} Result: {:}", bOk,convStr(cmp));
    }

    // NOK Case
    {
        int value1, value2;
        const bool bOk = CClassicErrorHandling::getNumericTableCellValue(db,{10},{.m_Column=0, .m_Row=1}, value1)
                         && CClassicErrorHandling::getNumericTableCellValue(db,{30},{.m_Column=4, .m_Row=0}, value2);
        std::strong_ordering cmp{std::strong_ordering::equal};
        if (bOk)
        {
            cmp = (value1 <=> value2);
        }
        printlnWrapper("Ok: {:} Result: {:}", bOk,convStr(cmp));
    }
}

bool CClassicErrorHandling::getElement(const CElementDatabase& db, const ElementKey& key, CElement& out)
{
    const auto iter = db.find(key);
    if (iter == db.cend())
    {
        log("Element not found in database");
        return false;
    }
    out = iter->second;
    return true;
}

bool CClassicErrorHandling::getTable(const CElement& element, CTableData& out)
{
    return getTypeData(element, out);
}

bool CClassicErrorHandling::getCell(const CTableData& tableData, const CCellLocation& location, CTableCell& out)
{
    if ( (location.m_Column >= tableData.m_Size.m_ColumnCount) ||
        (location.m_Row >= tableData.m_Size.m_RowCount ))
    {
        return false;
    }
    const auto index = location.m_Column+(location.m_Row*tableData.m_Size.m_ColumnCount);
    out = tableData.m_Cells[index];
    return true;
}

bool CClassicErrorHandling::getNumericCellValue(const CTableCell& cell, int& out)
{
    if ( ! std::holds_alternative<int>(cell.m_CellValue))
    {
        return false;
    }

    out = std::get<int>(cell.m_CellValue);
    return true;
}

bool CClassicErrorHandling::getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation, int& out)
{
    CElement element;
    if ( ! getElement(db, key, element))
    {
        return false;
    }

    CTableData tableData;
    if ( ! getTable(element, tableData))
    {
        return false;
    }

    CTableCell cell;
    if ( ! getCell(tableData, cellLocation, cell))
    {
        return false;
    }

    return getNumericCellValue(cell, out);
}

void CClassicErrorHandling::log(const std::string& message)
{
    printlnWrapper("Error: {:}", message);

#ifdef SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif
}
