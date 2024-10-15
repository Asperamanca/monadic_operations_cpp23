#ifndef RANGEMONAD_H
#define RANGEMONAD_H

#include <vector>
#include "../common/diagnosticinfo.h"

class CRangeMonad
{
public:
    static void compileAll(const std::vector<CProject>& projects);
};

#endif // RANGEMONAD_H
