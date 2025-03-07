#ifndef SHAREDFUNCTIONS_H
#define SHAREDFUNCTIONS_H

#include <string>

namespace mop
{

//NOTE: area should really be a type specifying a unit of area, but it is double for simplicity
std::string formatArea(const double area);
//NOTE: radius should really be a type specifying a unit of lenght, and the return value should be a unit of area,
// but it is double for simplicity
double calculateArea(const double radius);

} // namespace mop

#endif // SHAREDFUNCTIONS_H
