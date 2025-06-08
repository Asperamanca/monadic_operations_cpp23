#include "parsecommandline.h"
#include <string>

namespace mop
{

std::optional<int> getNumberFromCmdLine(int argc, char* argv[], const int indexToGet)
{
    if (argc <= indexToGet)
    {
        return {};
    }

    std::string cmdParam = argv[indexToGet];
    try
    {
        return std::stoi(cmdParam);
    }
    catch(...)
    {
        return {};
    }
}

} // namespace mop


