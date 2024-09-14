#include "expectedmonad.h"
#include <functional>

std::expected<CElement, CErrorInfo> CExpectedMonad::getElement(const CElementDatabase& db, const ElementKey& key)
{
    const auto iter = db.find(key);
    if (iter == db.cend())
    {
        return std::unexpected{CErrorInfo("Element not found in database")};
    }
    return {iter->second};
}

std::expected<CTableData, CErrorInfo> CExpectedMonad::getTable(const CElement& element)
{
    if ( ! std::holds_alternative<CTableData>(element.m_Data))
    {
        return std::unexpected{CErrorInfo("Element is not a table")};
    }
    return std::get<CTableData>(element.m_Data);
}

std::expected<CTableCell, CErrorInfo> CExpectedMonad::getCell(const CTableData& tableData, const CCellLocation& location)
{
    if ( (location.m_Column >= tableData.m_Size.m_ColumnCount) ||
        (location.m_Row >= tableData.m_Size.m_RowCount ))
    {
        return std::unexpected{CErrorInfo("Invalid cell location")};
    }
    const auto index = location.m_Column+(location.m_Row*tableData.m_Size.m_ColumnCount);
    return tableData.m_Cells[index];
}

std::expected<int, CErrorInfo> CExpectedMonad::getNumericCellValue(const CTableCell& cell)
{
    if ( ! std::holds_alternative<int>(cell.m_CellValue))
    {
        return std::unexpected{CErrorInfo("Cell does not contain numeric value")};
    }

    return std::get<int>(cell.m_CellValue);
}

bool CExpectedMonad::isNegative(const int value)
{
    return (value < 0);
}

std::expected<bool, CErrorInfo> CExpectedMonad::isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
#ifdef SUPPORTS_BIND_BACK
    return getElement(db, key)
            .and_then(getTable)
            .and_then(std::bind_back(&getCell,cellLocation))
            .and_then(getNumericCellValue)
            .transform(isNegative)
        .or_else(log<bool>);
#else
    return getElement(db, key)
        .and_then(getTable)
        .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
        .and_then(getNumericCellValue)
        .transform(isNegative)
        .or_else(log<bool>);
#endif
}

std::expected<int, CErrorInfo> CExpectedMonad::getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
#ifdef SUPPORTS_BIND_BACK
    return getElement(db, key)
            .and_then(getTable)
            .and_then(std::bind_back(&getCell,cellLocation))
            .and_then(getNumericCellValue)
        .or_else(log<int>);
#else
    return getElement(db, key)
        .and_then(getTable)
        .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
        .and_then(getNumericCellValue)
        .or_else(log<int>);
#endif
}

void CExpectedMonad::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        auto exValue = isNumericTableCellValueNegative(db, 10,CCellLocation{.m_Column=1, .m_Row=1});
        printlnWrapper("HasValue: {:} Value: {:}",exValue.has_value(),exValue.value_or(false));
    }

    // NOK Case
    {
        auto exValue = isNumericTableCellValueNegative(db, 10,CCellLocation{.m_Column=2, .m_Row=1});
        printlnWrapper("HasValue: {:} Value: {:}",exValue.has_value(),exValue.value_or(false));
    }
}

void CExpectedMonad::testForValueComparison()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        auto oCompare = compare(getNumericTableCellValue(db,10,{.m_Column=0,.m_Row=1}),
                                getNumericTableCellValue(db,30,{.m_Column=1,.m_Row=0}));

        printlnWrapper("HasValue: {:} Value: {:}",oCompare.has_value(),convStr(oCompare.value_or(std::strong_ordering::equivalent)));
    }

    // NOK Case
    {
        auto oCompare = compare(getNumericTableCellValue(db,10,{.m_Column=0,.m_Row=1}),
                                getNumericTableCellValue(db,30,{.m_Column=4,.m_Row=0}));

        printlnWrapper("HasValue: {:} Value: {:}",oCompare.has_value(),convStr(oCompare.value_or(std::strong_ordering::equivalent)));
    }
}
