#include "optionalmonad.h"
#include <string>

namespace mop
{

std::optional<bool> COptionalMonad::isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    return getElement(db, key)
        .and_then(getTable)
        .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
        .and_then(getNumericCellValue)
        .transform(isNegative)
        .or_else(log<bool>);
}


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

void COptionalMonad::compilerErrorFunctionReturnsNonOptionalWhenItShould()
{
    // Values don't matter - it won't compile
    CElementDatabase db{};
    ElementKey key{};
    CCellLocation cellLocation{};

    auto fGetNumericCellValueWrong = [](const CTableCell& cell) -> int
        {
            return 0;
        };

    // auto result = getElement(db, key)
    //     .and_then(getTable)
    //     .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
    //     .and_then(fGetNumericCellValueWrong)
    //     .transform(isNegative)
    //     .or_else(log<bool>);

    // Disable warnings because we cannot enable the non-compiling code that would use these symbols
    std::ignore = key;
    std::ignore = cellLocation;
    std::ignore = fGetNumericCellValueWrong;
}

void COptionalMonad::compilerErrorFunctionReturnsWrongValueType()
{
    // Values don't matter - it won't compile
    CElementDatabase db{};
    ElementKey key{};
    CCellLocation cellLocation{};

    auto fGetNumericCellValueWrong = [](const CTableCell& cell) -> std::optional<std::string>
    {
        return {};
    };

    // auto result = getElement(db, key)
    //     .and_then(getTable)
    //     .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
    //     .and_then(fGetNumericCellValueWrong)
    //     .transform(isNegative)
    //     .or_else(log<bool>);

    // Disable warnings because we cannot enable the non-compiling code that would use these symbols
    std::ignore = key;
    std::ignore = cellLocation;
    std::ignore = fGetNumericCellValueWrong;
}

void COptionalMonad::compilerErrorFunctionArgumentTypeMismatch()
{
    // Values don't matter - it won't compile
    CElementDatabase db{};
    ElementKey key{};
    CCellLocation cellLocation{};

    auto fGetNumericCellValueWrong = [](const ElementKey& key) -> std::optional<int>
    {
        return {};
    };

    // auto result = getElement(db, key)
    //     .and_then(getTable)
    //     .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
    //     .and_then(fGetNumericCellValueWrong)
    //     .transform(isNegative)
    //     .or_else(log<bool>);

    // Disable warnings because we cannot enable the non-compiling code that would use these symbols
    std::ignore = key;
    std::ignore = cellLocation;
    std::ignore = fGetNumericCellValueWrong;
}

std::optional<int> getNumericCellValueOverloaded(const CTableCell& cell)
{
    return 0;
}

std::optional<int> getNumericCellValueOverloaded(const int value)
{
    return 0;
}

void COptionalMonad::compilerErrorFunctionOverloadResolution()
{
    // Values don't matter - it won't compile
    CElementDatabase db{};
    ElementKey key{};
    CCellLocation cellLocation{};

    // auto result = getElement(db, key)
    //     .and_then(getTable)
    //     .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
    //     .and_then(getNumericCellValueOverloaded)
    //     .transform(isNegative)
    //     .or_else(log<bool>);

    // Disable warnings because we cannot enable the non-compiling code that would use these symbols
    std::ignore = key;
    std::ignore = cellLocation;
}

} // namespace mop

