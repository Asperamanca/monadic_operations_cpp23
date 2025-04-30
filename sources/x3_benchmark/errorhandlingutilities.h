#ifndef ERRORHANDLINGUTILITIES_H
#define ERRORHANDLINGUTILITIES_H

#include <optional>
#include <expected>

namespace mop
{

template<int V>
bool acceptEverythingExceptVClassic(const int in, int& out)
{
    if (in == V)
    {
        return false;
    }
    out = in;
    return true;
}

template<int V>
std::optional<int> acceptEverythingExceptVOptional(const int in)
{
    if (in == V)
    {
        return {};
    }
    return in;
}

template<int V>
int acceptEverythingExceptVException(const int in)
{
    if (in==V)
    {
        throw V;
    }
    return in;
}

enum class EError : int
{
    NotV = 1,
};

template<int V>
std::expected<int,EError> acceptEverythingExceptVExpected(const int in)
{
    if (in == V)
    {
        return std::unexpected(EError::NotV);
    }
    return in;
}

} // namespace mop

#endif // ERRORHANDLINGUTILITIES_H
