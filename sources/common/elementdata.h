#ifndef ELEMENTDATA_H
#define ELEMENTDATA_H

#include <unordered_map>
#include <variant>
#include <vector>
#include <string>

namespace mop
{

using ElementKey = int;

// NOTE: All through this file, I use public data members
//  This makes these classes flexible to use in my examples,
//  but offers no protection against misuse.
// In real code, I would make data members of more complex classes
//  (read: classes that need to uphold invariants) private,
//  and offer access methods



using CValue = std::variant<std::monostate,
                            bool,
                            int,
                            std::string>;

class CTableCell
{
public:
    CValue m_CellValue{};
};

class CTableSize
{
public:
    std::size_t m_ColumnCount{};
    std::size_t m_RowCount{};
};

class CCellLocation
{
public:
    // Zero-based
    std::size_t m_Column{};
    std::size_t m_Row{};
};

class CTableData
{
public:
    CTableSize m_Size{};
    std::vector<CTableCell> m_Cells{};
};

class CTreeData
{
public:
    // Something
};

class CPoint
{
public:
    int m_X{};
    int m_Y{};
};

class CTrendData
{
public:
    std::vector<CPoint> m_Points{};
};


using ElementData = std::variant<std::monostate,
                                 CTableData,
                                 CTreeData,
                                 CTrendData>;

class CElement
{
public:
    ElementKey m_Key;
    ElementData m_Data;
};


using CElementDatabase = std::unordered_map<ElementKey, CElement>;

CTableData createTestTable(const CTableSize& tableSize,
                           const std::vector<CValue>& initialValues);

CElementDatabase createTrendTestDatabase();
CElementDatabase createTableTestDatabase();

} // namespace mop

#endif // ELEMENTDATA_H
