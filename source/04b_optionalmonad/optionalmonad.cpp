#include "optionalmonad.h"
#include <functional>

std::optional<CElement> COptionalMonad::getElement(const CElementDatabase& db, const ElementKey& key)
{
    const auto iter = db.find(key);
    if (iter == db.cend())
    {
        return{};
    }
    return iter->second;
}

std::optional<CTableData> COptionalMonad::getTable(const CElement& element)
{
    if ( ! std::holds_alternative<CTableData>(element.m_Data))
    {
        return {};
    }
    return std::get<CTableData>(element.m_Data);
}

std::optional<CTableCell> COptionalMonad::getCell(const CTableData& tableData, const CCellLocation& location)
{
    if ( (location.m_Column >= tableData.m_Size.m_ColumnCount) ||
         (location.m_Row >= tableData.m_Size.m_RowCount ))
    {
        return {};
    }
    const auto index = location.m_Column+(location.m_Row*tableData.m_Size.m_ColumnCount);
    return tableData.m_Cells[index];
}

std::optional<int> COptionalMonad::getNumericCellValue(const CTableCell& cell)
{
    if ( ! std::holds_alternative<int>(cell.m_CellValue))
    {
        return {};
    }

    return std::get<int>(cell.m_CellValue);
}

bool COptionalMonad::isNegative(const int value)
{
    return (value < 0);
}

std::optional<bool> COptionalMonad::isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    return getElement(db, key)
        .and_then(getTable)
        .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
        .and_then(getNumericCellValue)
        .transform(isNegative)
        .or_else(log<bool>);
}

std::optional<int> COptionalMonad::getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& location)
{
    return getElement(db, key)
        .and_then(getTable)
        .and_then([location](const CTableData& table) {return getCell(table, location);})
        .and_then(getNumericCellValue)
        .or_else(log<int>);
}

std::optional<std::strong_ordering> COptionalMonad::compare(const std::optional<int>& left, const std::optional<int>& right)
{
    if ( ! (left.has_value() && right.has_value()))
    {
        return {};
    }

    return *left <=> *right;
}

std::optional<bool> COptionalMonad::isNumericTableCellValueNegativeWithIfs(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    auto oElement = getElement(db,key);
    if ( ! oElement.has_value())
    {
        return {};
    }

    auto oTable = getTable(oElement.value());
    if ( ! oTable.has_value())
    {
        return {};
    }

    auto oCell = getCell(oTable.value(),cellLocation);
    if ( ! oCell.has_value())
    {
        return {};
    }

    auto oValue = getNumericCellValue(oCell.value());
    if ( ! oValue.has_value())
    {
        return {};
    }
    return (oValue.value() < 0);
}

void COptionalMonad::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        auto oValue = isNumericTableCellValueNegative(db, 10,CCellLocation{.m_Column=1, .m_Row=1});
        printlnWrapper("HasValue: {:} Value: {:}",oValue.has_value(),oValue.value_or(false));
    }

    // NOK Case
    {
        auto oValue = isNumericTableCellValueNegative(db, 10,CCellLocation{.m_Column=2, .m_Row=1});
        printlnWrapper("HasValue: {:} Value: {:}",oValue.has_value(),oValue.value_or(false));
    }
}

void COptionalMonad::testForValueComparison()
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


void testMbindIdentity()
{
    auto wrapped = std::optional<std::optional<int>>{5};
    auto unwrapped = wrapped.and_then(std::identity{});
    // Type of 'start': std::optional<std::optional<int>>
    // Type of 'end'  :               std::optional<int>
    // I 'joined' by using and_then (=a "monadic bind") and an identity function
}
