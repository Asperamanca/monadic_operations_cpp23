#ifndef POINTERCLASSIC_H
#define POINTERCLASSIC_H

#include "../common/elementdata.h"
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include <format>
#include <optional>

namespace mop
{

class CPointersClassic
{
public:
    static std::optional<bool> getNumericTableValueNegative(const CElementDatabase& db, const ElementKey& key, const CCellLocation& cellLocation);

    static void testForNegativeNumericValue();

private:
    static const CElement* getElementPtr(const CElementDatabase& db, const ElementKey& key);
    template<class T>
    static const T* getTypeDataPtr(const CElement& element);
    static const CTableData* getTablePtr(const CElement& element);
    static const CTableCell* getCellPtr(const CTableData& tableData, const CCellLocation& location);
    // Functions returning a value type use std::optional
    static std::optional<int> getNumericCellValue(const CTableCell& cell);
};

template<class T>
const T* CPointersClassic::getTypeDataPtr(const CElement& element)
{
    if ( ! std::holds_alternative<T>(element.m_Data))
    {
        log(std::format("Element is not of type {:}",typeid(T).name()));
        return nullptr;
    }

    return &std::get<T>(element.m_Data);
}

} // namespace mop

#endif // POINTERCLASSIC_H
