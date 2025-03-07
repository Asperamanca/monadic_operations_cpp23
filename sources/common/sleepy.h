#ifndef SLEEPY_H
#define SLEEPY_H

#include <string>

namespace mop
{

// Simulate functions which take longer to compute
// The exact duration will vary by input parameter (but is the same for identical inputs)
class CSleepy
{
public:
    static std::string formatArea(const double area);
    static double calculateArea(const double radius);
};

} // namespace mop

#endif // SLEEPY_H
