#include "classicerrorhandling.h"
#include "../common/printutils.h"
#include "legacyupgrade.h"

namespace mop
{

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
        // Column '1' of key '10' is numeric and negative
        const bool bOk = CClassicErrorHandling::getNumericTableValueNegative(db,{10},{.m_Column=1, .m_Row=1}, bResult);
        printlnWrapper("Ok: {:} Result: {:}", bOk,bResult);
    }

    // NOK Case
    {
        bool bResult{};
        // Column '2' of key '10' is a string
        const bool bOk = CClassicErrorHandling::getNumericTableValueNegative(db,{10},{.m_Column=2, .m_Row=1}, bResult);
        printlnWrapper("Ok: {:} Result: {:}", bOk,bResult);
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

std::optional<bool> CClassicErrorHandling::isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    auto fGetElement = wrapOutParamToOptional<CElement>(getElement);
    auto fGetTable = wrapOutParamToOptional<CTableData>(getTable);
    auto fGetCell = wrapOutParamToOptional<CTableCell>(getCell);
    auto fGetNumericCellValue = wrapOutParamToOptional<int>(getNumericCellValue);

    return fGetElement(db, key)
            .and_then(fGetTable)
            .and_then([cellLocation, fGetCell](const CTableData& tableData) { return fGetCell(tableData, cellLocation);})
            .and_then(fGetNumericCellValue)
            .transform([](const int value) { return value < 0;} );
}

void CClassicErrorHandling::testLegacyCodeUpgrade()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        // Column '1' of key '10' is numeric and negative
        const auto oResult = CClassicErrorHandling::isNumericTableCellValueNegative(db,{10},{.m_Column=1, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(),oResult.value_or(false));
    }

    // NOK Case
    {
        // Column '2' of key '10' is a string
        const auto oResult = CClassicErrorHandling::isNumericTableCellValueNegative(db,{10},{.m_Column=2, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(),oResult.value_or(false));
    }
}

} // namespace mop

