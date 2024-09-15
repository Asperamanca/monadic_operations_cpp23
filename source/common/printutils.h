#ifndef PRINTUTILS_H
#define PRINTUTILS_H

#include "compilerinfo.h" // IWYU pragma: keep
#ifdef SUPPORTS_PRINT
#    include <print>
#else
#include <iostream>
#endif
#include <format>
#include <type_traits>

template <class... _Types>
void printlnWrapper(std::format_string<_Types...> _Fmt, _Types&&... _Args)
{
#ifdef SUPPORTS_PRINT
    std::println(_Fmt, std::forward<_Types>(_Args)...);
#else
    std::cout << std::format(_Fmt,std::forward<_Types>(_Args)...) << "\n";
#endif
}

void printStringRange(const auto& range)
{
    for(const auto& item : range)
    {
        printlnWrapper("{:}",item);
    }
}

template<class T>
std::string formatTypeInfo()
{
    static_assert( ! std::is_pointer<T>(),"Pointer types currently not supported");
    return std::format("{:}{:}{:}{:}",
                       std::is_reference<T>()
                            ? std::is_const<typename std::remove_reference<T>::type>() ? "const " : ""
                            : std::is_const<T>() ? "const " : "",
                       typeid(T).name(),
                       std::is_reference<T>() ? "&" : "",
                       std::is_rvalue_reference<T>() ? "&" : "");
}



#endif // PRINTUTILS_H
