#include "sharedfunctions.h"
#include <numbers>
#include <format>
#include <cmath>

namespace mop
{

std::string formatArea(const double area)
{
    // Trick to verify the source file is interpreted as UTF-8 - enable to check!
    // See https://devblogs.microsoft.com/oldnewthing/20241231-00/?p=110696
    // static_assert(L'☃' == L'\x2603', "File encoding appears to be corrupted.");

    // If the 'squared' character is incorrectly displayed in output, check if
    //  the encoding of the output terminal is UTF-8
    return std::format("{:} m²", area);
}

double calculateArea(const double radius)
{
    return std::pow(radius, 2.0) * std::numbers::pi;
}

} // namespace mop

