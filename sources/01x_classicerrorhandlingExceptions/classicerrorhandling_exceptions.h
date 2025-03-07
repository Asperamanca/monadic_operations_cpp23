#ifndef CLASSICERRORHANDLING_EXCEPTIONS_H
#define CLASSICERRORHANDLING_EXCEPTIONS_H

#include "../common/elementdata.h"
#include <string>


namespace mop
{

class CClassicErrorHandlingExceptions
{
private:
    static CElement getElement(const CElementDatabase& db, const ElementKey& key);
    template<class T>
    static T getTypeData(const CElement& element);
    static CTableData getTable(const CElement& element);
    static CTableCell getCell(const CTableData& tableData, const CCellLocation& location);
    static int getNumericCellValue(const CTableCell& cell);
    static void log(const std::string& message);

    static int getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& location);
public:
    static bool isNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);

    static void testForNegativeNumericValue();
};

template<class T>
T CClassicErrorHandlingExceptions::getTypeData(const CElement& element)
{
    // Throws exception on type mismatch
    return std::get<T>(element.m_Data);
}

} // namespace mop

#endif // CLASSICERRORHANDLING_EXCEPTIONS_H
