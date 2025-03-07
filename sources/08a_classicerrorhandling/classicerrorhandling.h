#ifndef CLASSICERRORHANDLING_H
#define CLASSICERRORHANDLING_H

#include "../common/elementdata.h"
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include <format>
#include <optional>

namespace mop
{


class CClassicErrorHandling
{
public:
    static bool getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation, bool& result);

    static void testForNegativeNumericValue();
private:
    static bool getElement(const CElementDatabase& db, const ElementKey& key, CElement& element);
    template<class T>
    static bool getTypeData(const CElement& element, T& out);
    static bool getTable(const CElement& element, CTableData& out);
    static bool getCell(const CTableData& tableData, const CCellLocation& location, CTableCell& out);
    static bool getNumericCellValue(const CTableCell& cell, int& out);
    static bool getNumericTableCellValue(const CElementDatabase& db, const ElementKey& key, const CCellLocation& location, int& out);

public:
    // Shows how a code upgrade using a wrapper could work
    // Not recommended on large scale - temporary solution until the code upgrade is done!
    static std::optional<bool> isNumericTableCellValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);
    static void testLegacyCodeUpgrade();
};



template<class T>
bool CClassicErrorHandling::getTypeData(const CElement& element, T& out)
{
    if ( ! std::holds_alternative<T>(element.m_Data))
    {
        log(std::format("Element is not of type {:}",typeid(T).name()));
        return false;
    }

    out = std::get<T>(element.m_Data);
    return true;
}

} // namespace mop

#endif // CLASSICERRORHANDLING_H
