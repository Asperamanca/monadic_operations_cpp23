#include "noisy.h"
#include <algorithm>
#include "../common/printutils.h"

CNoisy::CNoisy()
{
    printlnWrapper("Default constructed");
}

CNoisy::CNoisy(const int value)
{
    std::ranges::fill(m_Data,value);
    printlnWrapper("Value constructed");
}

CNoisy::~CNoisy()
{
    printlnWrapper("Destructed");
}

CNoisy::CNoisy(const CNoisy& other)
    : m_Data(other.m_Data)
{
    printlnWrapper("Copy-constructed");
}

CNoisy& CNoisy::operator=(const CNoisy& other)
{
    auto copy = other;
    swap(copy, *this);
    printlnWrapper("Copy-assigned");
    return *this;
}

CNoisy::CNoisy(CNoisy&& other) noexcept
    : m_Data(std::move(other.m_Data))
{
    printlnWrapper("Move-constructed");
}

CNoisy& CNoisy::operator=(CNoisy&& other) noexcept
{
    m_Data = std::move(other.m_Data);
    printlnWrapper("Move-assigned");
    return *this;
}

void swap(CNoisy& left, CNoisy& right) noexcept
{
    using std::swap;
    swap(left.m_Data, right.m_Data);
    printlnWrapper("Swapped");
}



// // cout version for older compilers
// #include <iostream>

// CNoisy::CNoisy()
// {
//     std::cout <<"Default constructed\n";
// }

// CNoisy::CNoisy(const int value)
// {
//     std::ranges::fill(m_Data,value);
//     std::cout <<"Value constructed\n";
// }

// CNoisy::~CNoisy()
// {
//     std::cout <<"Destructed\n";
// }

// CNoisy::CNoisy(const CNoisy& other)
//     : m_Data(other.m_Data)
// {
//     std::cout <<"Copy-constructed\n";
// }

// CNoisy& CNoisy::operator=(const CNoisy& other)
// {
//     auto copy = other;
//     swap(copy, *this);
//     std::cout <<"Copy-assigned\n";
//     return *this;
// }

// CNoisy::CNoisy(CNoisy&& other) noexcept
//     : m_Data(std::move(other.m_Data))
// {
//     std::cout <<"Move-constructed\n";
// }

// CNoisy& CNoisy::operator=(CNoisy&& other) noexcept
// {
//     m_Data = std::move(other.m_Data);
//     std::cout <<"Move-assigned\n";
//     return *this;
// }

// void swap(CNoisy& left, CNoisy& right) noexcept
// {
//     using std::swap;
//     swap(left.m_Data, right.m_Data);
//     std::cout <<"Swapped\n";
// }

