#ifndef NOISY_H
#define NOISY_H

#include <array>

class CNoisy
{
public:
    CNoisy();
    CNoisy(const int value);
    ~CNoisy();
    CNoisy(const CNoisy& other);
    CNoisy& operator=(const CNoisy& other);
    CNoisy(CNoisy&& other) noexcept;
    CNoisy& operator=(CNoisy&& other) noexcept;
    friend void swap(CNoisy& left, CNoisy& right) noexcept;

private:
    std::array<int,100> m_Data{};
};
#endif // NOISY_H
