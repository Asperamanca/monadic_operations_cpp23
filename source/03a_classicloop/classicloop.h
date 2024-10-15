#ifndef CLASSICLOOP_H
#define CLASSICLOOP_H

#include <vector>
#include "../common/diagnosticinfo.h"

class CClassicLoop
{
public:
    static void compileAll(const std::vector<CProject>& folders);
};

#endif // CLASSICLOOP_H
