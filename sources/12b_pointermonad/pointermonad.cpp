#include "pointermonad.h"
#include "../common/printutils.h"

namespace mop
{

std::optional<bool> CPointerMonad::getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    return CPtr(getElementPtr(db,key))
            .and_then(getTablePtr)
            .and_then([cellLocation](const auto& tableData){return getCellPtr(tableData,cellLocation);})
            .and_then(getNumericCellValue)
            .transform(isNegative);
}

void CPointerMonad::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        // Column '1' of key '10' is numeric and negative
        const auto oResult = CPointerMonad::getNumericTableValueNegative(db,{10},{.m_Column=1, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(), oResult.value_or(false));
    }

    // NOK Case
    {
        // Column '2' of key '10' is a string
        const auto oResult = CPointerMonad::getNumericTableValueNegative(db,{10},{.m_Column=2, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(), oResult.value_or(false));
    }
}

const CElement* CPointerMonad::getElementPtr(const CElementDatabase& db, const ElementKey& key)
{
    const auto iter = db.find(key);
    if (iter == db.cend())
    {
        log("Element not found in database");
        return nullptr;
    }
    return &iter->second;
}

const CTableData* CPointerMonad::getTablePtr(const CElement& element)
{
    return getTypeDataPtr<CTableData>(element);
}

const CTableCell* CPointerMonad::getCellPtr(const CTableData& tableData, const CCellLocation& location)
{
    if ( (location.m_Column >= tableData.m_Size.m_ColumnCount) ||
        (location.m_Row >= tableData.m_Size.m_RowCount ))
    {
        return nullptr;
    }
    const auto index = location.m_Column+(location.m_Row*tableData.m_Size.m_ColumnCount);
    return &tableData.m_Cells[index];
}

std::optional<int> CPointerMonad::getNumericCellValue(const CTableCell& cell)
{
    if ( ! std::holds_alternative<int>(cell.m_CellValue))
    {
        return {};
    }

    return std::get<int>(cell.m_CellValue);
}

bool CPointerMonad::isNegative(const int value)
{
    return value < 0;
}


} // namespace mop

