#ifndef POINTERMONAD_H
#define POINTERMONAD_H

#include "../common/pointerscommon.h"
#include <type_traits>
#include <optional>
#include <functional>

template<class T>
concept cIsPointer = std::is_pointer_v<T>;

template<class T>
concept cHasValueType = requires{typename T::value_type;};

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


template<cIsPointer T>
template<class TCall>
auto CPtr<T>::and_then(TCall&& fInvoke)
{
    using TRef = std::add_lvalue_reference_t<std::remove_pointer_t<T>>;
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
    else //if constexpr (cHasValueType<TRet>) // TRet is a wrapper around something
    {
        // fInvoke returns a non-pointer. For now we require an optional.
        if (m_Ptr)
        {
            return std::invoke(std::forward<TCall>(fInvoke),*m_Ptr);
        }
        using TValue = TRet::value_type;
        static_assert(std::is_same_v<std::optional<TValue>,TRet>,"Return type is neither pointer nor std::optional");
        return std::remove_cvref_t<TRet>{};
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
    else //if constexpr (cHasValueType<TRet>) // TRet is a wrapper around something
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
private:
    static bool isObjectValid(CPtr<CDatabase*> pDb,
                              const CContainerKey keyContainer,
                              const CObjectKey keyObject);

    static CNode* getNodeParent(CNode& node);
    static CNode* getNodeChild(CNode& parent, const CNodeKey& childKey);
    static CContent getNodeContent(CNode& node);
    static std::optional<int> getContentNumericValue(const CContent& content);
    static std::optional<int> getNodeNumericValue(CNode& node);
    static std::optional<int> getSiblingValueSquared(CNode* pNodeStart, const CNodeKey& siblingKey);
    static int makeSquared(const int value);

public:
    static void testObjectValid();
    static void testNodeSiblingValueSquared();
};

#endif // POINTERMONAD_H
