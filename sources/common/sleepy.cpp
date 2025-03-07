#include "sleepy.h"
#include <format>
#include <numbers>
#include <cmath>
#include <thread>
using namespace std::chrono_literals;

namespace mop
{

std::string CSleepy::formatArea(const double area)
{
    // Trick to verify the source file is interpreted as UTF-8 - enable to check!
    // See https://devblogs.microsoft.com/oldnewthing/20241231-00/?p=110696
    // static_assert(L'☃' == L'\x2603', "File encoding appears to be corrupted.");

    // If the 'squared' character is incorrectly displayed in output, check if
    //  the encoding of the output terminal is UTF-8

    const auto sleepOffset = (std::lround(area) % 20L) * 10L;
    std::this_thread::sleep_for(100ms + std::chrono::milliseconds(sleepOffset));
    return std::format("{:} m²", area);
}

double CSleepy::calculateArea(const double radius)
{
    const auto sleepOffset = (std::lround(radius) % 20L) * 10L;
    std::this_thread::sleep_for(140ms + std::chrono::milliseconds(sleepOffset));
    return std::pow(radius, 2.0) * std::numbers::pi;
}

} // namespace mop

