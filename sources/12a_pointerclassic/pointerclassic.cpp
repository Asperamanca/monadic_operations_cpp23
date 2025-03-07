#include "pointerclassic.h"
#include "../common/printutils.h" // IWYU pragma: keep

namespace mop
{

std::optional<bool> CPointersClassic::getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
{
    if ( const auto* const pElement = getElementPtr(db, key))
    {
        if (const auto* const pTableData = getTablePtr(*pElement))
        {
            if (const auto* const pCell = getCellPtr(*pTableData, cellLocation))
            {
                if (auto oValue = getNumericCellValue(*pCell))
                {
                    return oValue.value() < 0;
                }
            }
        }
    }
    return {};
}

void CPointersClassic::testForNegativeNumericValue()
{
    const auto db = createTableTestDatabase();

    // OK Case
    {
        // Column '1' of key '10' is numeric and negative
        const auto oResult = CPointersClassic::getNumericTableValueNegative(db,{10},{.m_Column=1, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(), oResult.value_or(false));
    }

    // NOK Case
    {
        // Column '2' of key '10' is a string
        const auto oResult = CPointersClassic::getNumericTableValueNegative(db,{10},{.m_Column=2, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(), oResult.value_or(false));
    }
}

const CElement* CPointersClassic::getElementPtr(const CElementDatabase& db, const ElementKey& key)
{
    const auto iter = db.find(key);
    if (iter == db.cend())
    {
        log("Element not found in database");
        return nullptr;
    }
    return &iter->second;
}

const CTableData* CPointersClassic::getTablePtr(const CElement& element)
{
    return getTypeDataPtr<CTableData>(element);
}

const CTableCell* CPointersClassic::getCellPtr(const CTableData& tableData, const CCellLocation& location)
{
    if ( (location.m_Column >= tableData.m_Size.m_ColumnCount) ||
        (location.m_Row >= tableData.m_Size.m_RowCount ))
    {
        return nullptr;
    }
    const auto index = location.m_Column+(location.m_Row*tableData.m_Size.m_ColumnCount);
    return &tableData.m_Cells[index];
}

std::optional<int> CPointersClassic::getNumericCellValue(const CTableCell& cell)
{
    if ( ! std::holds_alternative<int>(cell.m_CellValue))
    {
        return {};
    }

    return std::get<int>(cell.m_CellValue);
}

} // namespace mop

