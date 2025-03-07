#ifndef CLASSICLOOP_H
#define CLASSICLOOP_H

#include <vector>
#include "../common/diagnosticinfo.h"

namespace mop
{

class CClassicLoop
{
public:
    static void compileAll(const std::vector<CProject>& projects);
};

} // namespace mop

#endif // CLASSICLOOP_H
