#ifndef PRINTUTILS_H
#define PRINTUTILS_H

#include "compilerinfo.h" // IWYU pragma: keep
#ifdef MOP_SUPPORTS_PRINT
#    include <print>
#else
#include <iostream>
#endif
#include <format>
#include <type_traits>

namespace mop
{

// Wrapper for support of compilers that don't yet support std::println
template <class... _Types>
void printlnWrapper(std::format_string<_Types...> _Fmt, _Types&&... _Args)
{
#ifdef MOP_SUPPORTS_PRINT
    std::println(_Fmt, std::forward<_Types>(_Args)...);
#else
    std::cout << std::format(_Fmt,std::forward<_Types>(_Args)...) << "\n";
#endif
}


void printStringRange(const auto& range, auto fProjection)
{
    for(const auto& item : range)
    {
        printlnWrapper("{:}",fProjection(item));
    }
}

void printStringRange(const auto& range)
{
    printStringRange(range, std::identity());
}


template<class T>
std::string formatTypeInfo(const bool bPrintTypeName = true)
{
    if constexpr (std::is_pointer<T>())
    {
        return std::format("{:}{:}*{:}",
                           std::is_const<typename std::remove_pointer<T>::type>() ? "const " : "",
                           bPrintTypeName ? typeid(T).name() : "",
                           std::is_const<T>() ? " const" : "");
    }
    else
    {
        return std::format("{:}{:}{:}{:}",
                           std::is_reference<T>()
                                ? std::is_const<typename std::remove_reference<T>::type>() ? "const " : ""
                                : std::is_const<T>() ? "const " : "",
                           bPrintTypeName ? typeid(T).name() : "",
                           std::is_reference<T>() ? "&" : "",
                           std::is_rvalue_reference<T>() ? "&" : "");
    }
}

} // namespace mop

#endif // PRINTUTILS_H
