#include "elementdata.h"
#include <algorithm>
#include <iterator>

CElementDatabase createTrendTestDatabase()
{
    auto fCreateDbEntry = [](const ElementKey& key, auto&& data)
    {
        return std::make_pair(key, CElement{.m_Key = key, .m_Data = std::move(data)});
    };

    CElementDatabase db{{fCreateDbEntry(1,CTreeData()),
                         fCreateDbEntry(2,CTableData()),
                         fCreateDbEntry(3,CTrendData()),
                         fCreateDbEntry(5,CTrendData{.m_Points{CPoint{.m_X = 3, .m_Y=5},
                                                                CPoint{.m_X = 5, .m_Y= 2},
                                                                CPoint{.m_X = 10,.m_Y = -1}}})}};
    return db;
}

CElementDatabase createTableTestDatabase()
{
    auto fCreateDbEntry = [](const ElementKey& key, auto&& data)
    {
        return std::make_pair(key, CElement{.m_Key = key, .m_Data = std::move(data)});
    };

    CElementDatabase db{{fCreateDbEntry(10,createTestTable({.m_ColumnCount=3,.m_RowCount=5},{15,-12,"Hello"})),
                         fCreateDbEntry(20,createTestTable({.m_ColumnCount=2,.m_RowCount=3},{"No","Numbers"})),
                         fCreateDbEntry(30,createTestTable({.m_ColumnCount=4,.m_RowCount=2},{true,22,false,-1}))}};
    return db;
}

CTableData createTestTable(const CTableSize& tableSize, const std::vector<CValue>& initialValues)
{
    if (initialValues.empty())
    {
        return {};
    }
    auto initialIter = initialValues.begin();
    auto fInit = [&initialValues, &initialIter]() -> CTableCell
        {
            if (initialIter == initialValues.end())
            {
                initialIter = initialValues.begin();
            }
            auto value = *initialIter;
            ++initialIter;
            return {.m_CellValue=value};
        };

    CTableData data;
    data.m_Size = tableSize;
    std::generate_n(std::back_inserter(data.m_Cells),tableSize.m_ColumnCount*tableSize.m_RowCount,fInit);
    return data;
}
