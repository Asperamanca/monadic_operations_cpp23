#ifndef POINTERCLASSIC_H
#define POINTERCLASSIC_H

#include "../common/pointerscommon.h"
#include <optional>


class CPointersClassic
{
private:
    static bool isObjectValid(CDatabase* const pDb,
                              const CContainerKey keyContainer,
                              const CObjectKey keyObject);

    static CNode* getSiblingByKey(CNode* pNodeStart, const CNodeKey& siblingKey);
    static std::optional<int> getNodeNumericValue(CNode* pNode);
    static std::optional<int> getSiblingValueSquared(CNode* pNodeStart, const CNodeKey& siblingKey);
    static int makeSquared(const int value);
public:
    static void testObjectValid();
    static void testNodeSiblingValueSquared();
};


#endif // POINTERCLASSIC_H
