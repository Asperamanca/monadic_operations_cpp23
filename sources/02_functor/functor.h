#ifndef FUNCTOR_H
#define FUNCTOR_H

#include <type_traits>
#include <optional>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>


// This is stupid, because it does not do anything useful
// Still, it shows the basic pattern that makes more sense when wrapping the value with optional or vector (or...)
template<class TValue, class TCall>
auto liftStupid(TCall&& callable);

// Returns a function that will perform the passed 'callable' on a type wrapped in std::optional
template<class TValue, class TCall>
auto liftOptional(TCall&& callable);

// Returns a function that will perform the passed 'callable' on a type wrapped in std::vector
template<class TValue, class TCall>
auto liftVector(TCall&& callable);


// This is stupid, because it does not do anything useful
// Still, it shows the basic pattern that makes more sense when wrapping the value with optional or vector
// Compare to liftStupid - both versions offer functor functionality, but in different ways
template<class TValue>
class CFunctorStupid
{
public:
    CFunctorStupid(const TValue& initialValue);
    TValue result() const;

    template<class TCall>
    auto transform(TCall&& callable) const;
private:
    TValue m_Value{};
};

// An 'optional' wrapper around a value that allows it to apply a function through the optional
//  (without using C++23's monadic operations yet)
// Compare to liftOptional - both versions offer functor functionality, but in different ways
template<class TValue>
class CFunctorOpt
{
public:
    CFunctorOpt() = default;
    CFunctorOpt(const std::optional<TValue>& initialValue);
    std::optional<TValue> result() const;

    template<class TCall>
    auto transform(TCall&& callable) const;
private:
    std::optional<TValue> m_Value{};
};

// A 'vector' wrapper around a value that allows it to apply a function through the vector
// Compare to liftVector - both versions offer functor functionality, but in different ways
template<class TValue>
class CFunctorVec
{
public:
    CFunctorVec(const std::vector<TValue>& initialValue);
    std::vector<TValue> result() const;

    template<class TCall>
    auto transform(TCall&& callable) const;
private:
    std::vector<TValue> m_Values{};
};

template<class TValue, class TCall>
auto liftStupid(TCall&& callable)
{
    using TResult = std::remove_cvref_t<std::invoke_result_t<TCall, TValue>>;
    return [&](const TValue& in) -> TResult
    {
        return std::invoke(callable,in);
    };
}

template<class TValue, class TCall>
auto liftOptional(TCall&& callable)
{
    using TResult = std::remove_cvref_t<std::invoke_result_t<TCall, TValue>>;
    return [&](const std::optional<TValue>& oIn) -> std::optional<TResult>
    {
        if  ( ! oIn.has_value() )
        {
            return {};
        }
        return std::invoke(callable,oIn.value());
    };
}

template<class TValue, class TCall>
auto liftVector(TCall&& callable)
{
    using TResult = std::remove_cvref_t<std::invoke_result_t<TCall, TValue>>;
    return [&](const std::vector<TValue>& vecIn) -> std::vector<TResult>
        {
            std::vector<TResult> vecResult;
            vecResult.reserve(vecIn.size());
            std::ranges::transform(vecIn,std::back_inserter(vecResult),std::forward<TCall>(callable));
            return vecResult;
        };
}

template<class TValue>
CFunctorStupid<TValue>::CFunctorStupid(const TValue& initialValue)
    : m_Value(initialValue)
{
}

template<class TValue>
TValue CFunctorStupid<TValue>::result() const
{
    return m_Value;
}

template<class TValue>
template<class TCall>
auto CFunctorStupid<TValue>::transform(TCall&& callable) const
{
    using TResult = std::remove_cvref_t<std::invoke_result_t<TCall, TValue>>;
    return CFunctorStupid<TResult>(std::invoke(callable,m_Value));
}

template<class TValue>
CFunctorOpt<TValue>::CFunctorOpt(const std::optional<TValue>& initialValue)
    : m_Value(initialValue)
{
}


template<class TValue>
std::optional<TValue> CFunctorOpt<TValue>::result() const
{
    return m_Value;
}

template<class TValue>
template<class TCall>
auto CFunctorOpt<TValue>::transform(TCall&& callable) const
{
    using TResult = std::remove_cvref_t<std::invoke_result_t<TCall, TValue>>;
    using TRet = CFunctorOpt<TResult>;
    if (m_Value.has_value())
    {
        return TRet(std::invoke(callable,m_Value.value()));
    }
    return TRet{};
}

template<class TValue>
CFunctorVec<TValue>::CFunctorVec(const std::vector<TValue>& initialValue)
    : m_Values(initialValue)
{
}

template<class TValue>
std::vector<TValue> CFunctorVec<TValue>::result() const
{
    return m_Values;
}

template<class TValue>
template<class TCall>
auto CFunctorVec<TValue>::transform(TCall&& callable) const
{
    using TResult = std::remove_cvref_t<std::invoke_result_t<TCall, TValue>>;
    using TRet = CFunctorVec<TResult>;
    std::vector<TResult> vecResult{};
    vecResult.reserve(m_Values.size());
    std::ranges::transform(m_Values,std::back_inserter(vecResult),std::forward<TCall>(callable));
    return TRet(std::move(vecResult));
}


#endif // FUNCTOR_H
