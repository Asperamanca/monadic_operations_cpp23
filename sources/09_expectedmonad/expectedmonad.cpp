#include "expectedmonad.h"

namespace mop
{

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

void CExpectedMonad::testShowExpectedUsage()
{
    auto fGetExpected = [](const bool bValid) -> std::expected<int,CErrorInfo>
        {
            if (bValid)
            {
                return {42};
            }
            else
            {
                return std::unexpected{CErrorInfo("Requested error type")};
            }
        };

    auto exValue = fGetExpected(false);
    if (exValue.has_value())
    {
        auto value = exValue.value();
        std::ignore = value;
    }
    else
    {
        auto error = exValue.error();
        std::ignore = error;
    }

    if (auto exValue2 = fGetExpected(true))
    {
        auto value2 = exValue2.value();
        std::ignore = value2;
    }
    else
    {
        auto error2 = exValue2.error();
        std::ignore = error2;
    }

    auto value3 = fGetExpected(false).value_or(21);
    std::ignore = value3;
}

void CExpectedMonad::testExpectedTransformError()
{
    // Start with expected with 'std::string' error information
    std::expected<int,std::string> expectedWithErrorString{/*initialize somehow*/};

    auto fConvertErrorString = [](const std::string& errorString)
        {
            return CErrorInfo(errorString);
        };

    // Convert the error type
    std::expected<int,CErrorInfo> expectedWithErrorInfo = expectedWithErrorString.transform_error(fConvertErrorString);
}

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
    return getElement(db, key)
        .and_then(getTable)
        .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
        .and_then(getNumericCellValue)
        .transform(isNegative)
        .or_else(log<bool>);
}



std::expected<int, CErrorInfo> CExpectedMonad::getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    return getElement(db, key)
        .and_then(getTable)
        .and_then([cellLocation](const CTableData& tableData) {return getCell(tableData, cellLocation);})
        .and_then(getNumericCellValue)
        .or_else(log<int>);
}

} // namespace mop

