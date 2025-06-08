#ifndef PARSECOMMANDLINE_H
#define PARSECOMMANDLINE_H

#include <optional>

namespace mop
{

std::optional<int> getNumberFromCmdLine(int argc, char* argv[], const int indexToGet);

} // namespace mop

#endif // PARSECOMMANDLINE_H
