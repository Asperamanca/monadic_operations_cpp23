#include "classicerrorhandling_exceptions.h"
#include "../common/printutils.h"
#include "../common/utils.h"
#include "../common/stacktraceutils.h" // IWYU pragma: keep

namespace mop
{

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

#ifdef MOP_SUPPORTS_STACKTRACE
    dumpStack(std::stacktrace::current());
#else
    printlnWrapper("Your compiler does not support stacktrace");
#endif
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

bool CClassicErrorHandlingExceptions::isNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation)
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
        auto oResult = tryCall(CClassicErrorHandlingExceptions::isNumericTableValueNegative,db,ElementKey(10),CCellLocation{.m_Column=1, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(),oResult.value_or(false));
    }

    // NOK Case
    {
        auto oResult = tryCall(CClassicErrorHandlingExceptions::isNumericTableValueNegative,db,10,CCellLocation{.m_Column=2, .m_Row=1});
        printlnWrapper("Ok: {:} Result: {:}", oResult.has_value(),oResult.value_or(false));
    }
}

} // namespace mop
