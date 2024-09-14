#ifndef CLASSICERRORHANDLING_EXCEPTIONS_H
#define CLASSICERRORHANDLING_EXCEPTIONS_H

#include "../common/elementdata.h"
#include <string>
#include <optional>

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
    static std::optional<std::strong_ordering> compare(const std::optional<int>& left, const std::optional<int>& right);

    static int getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& location);
public:
    static bool getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);

    static void testForNegativeNumericValue();
    static void testForValueComparison();
};

template<class T>
T CClassicErrorHandlingExceptions::getTypeData(const CElement& element)
{
    // Throws exception on type mismatch
    return std::get<T>(element.m_Data);
}

#endif // CLASSICERRORHANDLING_EXCEPTIONS_H
