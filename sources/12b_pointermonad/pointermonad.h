#ifndef POINTERMONAD_H
#define POINTERMONAD_H

#include <type_traits>
#include <optional>
#include <functional>
#include <format>
#include "../common/stacktraceutils.h" // IWYU pragma: keep
#include "../common/elementdata.h"

namespace mop
{

template<class T>
concept cIsPointer = std::is_pointer_v<T>;

template<class T>
concept cHasValueType = requires{typename T::value_type;};

template<class> constexpr bool cbIsOptional = false;
template<class T> constexpr bool cbIsOptional<std::optional<T>> = true;

template<cIsPointer TPtr>
class CPtr
{
public:
    CPtr() = default;
    explicit CPtr(const TPtr& ptr);

    TPtr operator->() const noexcept;
    operator bool() const noexcept;
    bool operator!() const noexcept;

    template<class TCall>
    auto and_then(TCall&& fInvoke);

    // Variant of and_then that accepts extra arguments and passes them on to fInvoke
    template<class TCall, class... TArgs>
    auto and_then_args(TCall&& fInvoke, TArgs&&... args);
private:
    TPtr m_Ptr{};
};


template<cIsPointer TPtr>
template<class TCall>
auto CPtr<TPtr>::and_then(TCall&& fInvoke)
{
    using TRef = std::add_lvalue_reference_t<std::remove_pointer_t<TPtr>>;
    using TRet = std::invoke_result_t<TCall,TRef>;
    if constexpr (cIsPointer<TRet>)
    {
        // fInvoke returns a pointer
        if (m_Ptr)
        {
            return CPtr<TRet>(std::invoke(std::forward<TCall>(fInvoke),*m_Ptr));
        }
        return CPtr<TRet>{};
    }
    else if constexpr (cbIsOptional<TRet>)
    {
        // fInvoke returns a non-pointer. For now we require an optional.
        if (m_Ptr)
        {
            return std::invoke(std::forward<TCall>(fInvoke),*m_Ptr);
        }
        return std::remove_cvref_t<TRet>{};
    }
    // else if constexpr (function already returns CPtr) ...
    // else if constexpr (function returns std::expected) ...
    else
    {
        static_assert(false, "fInvoke returns neither pointer nor optional");
    }
}


// Version which accepts extra arguments and passes them to fInvoke
//
template<cIsPointer TPtr>
template<class TCall, class... TArgs>
auto CPtr<TPtr>::and_then_args(TCall&& fInvoke, TArgs&&... args)
{
    using TRef = std::add_lvalue_reference_t<std::remove_pointer_t<TPtr>>;
    using TRet = std::invoke_result_t<TCall,TRef,TArgs...>;
    static_assert(std::is_invocable_v<TCall,TRef, TArgs...>);
    if constexpr (cIsPointer<TRet>)
    {
        // fInvoke returns a pointer
        if (m_Ptr)
        {
            return CPtr<TRet>(std::invoke(std::forward<TCall>(fInvoke),*m_Ptr,std::forward<TArgs>(args)...));
        }
        return CPtr<TRet>{};
    }
    else if constexpr (cbIsOptional<TRet>)
    {
        // fInvoke returns a non-pointer. For now we require an optional.
        using TValue = TRet::value_type;
        static_assert(std::is_same_v<std::optional<TValue>,TRet>,"Return type is neither pointer nor std::optional");
        if (m_Ptr)
        {
            return std::invoke(std::forward<TCall>(fInvoke),*m_Ptr,std::forward<TArgs>(args)...);
        }
        return std::remove_cvref_t<TRet>{};
    }
    else
    {
        static_assert(false, "fInvoke returns neither pointer nor optional");
    }
}


template<cIsPointer TPtr>
CPtr<TPtr>::CPtr(const TPtr& ptr)
    : m_Ptr(ptr)
{
}

template<cIsPointer TPtr>
TPtr CPtr<TPtr>::operator->() const noexcept
{
    return m_Ptr;
}

template<cIsPointer TPtr>
CPtr<TPtr>::operator bool() const noexcept
{
    return m_Ptr;
}

template<cIsPointer TPtr>
bool CPtr<TPtr>::operator!() const noexcept
{
    return ! m_Ptr;
}





class CPointerMonad
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
    static bool isNegative(const int value);
};

template<class T>
const T* CPointerMonad::getTypeDataPtr(const CElement& element)
{
    if ( ! std::holds_alternative<T>(element.m_Data))
    {
        log(std::format("Element is not of type {:}",typeid(T).name()));
        return nullptr;
    }

    return &std::get<T>(element.m_Data);
}

} // namespace mop

#endif // POINTERMONAD_H
