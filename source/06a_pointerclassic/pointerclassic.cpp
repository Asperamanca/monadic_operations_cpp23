#include "pointerclassic.h"
#include "../common/printutils.h"



bool CPointersClassic::isObjectValid(CDatabase* const pDb, const CContainerKey keyContainer, const CObjectKey keyObject)
{
    if ( ! pDb)
    {
        return false;
    }
    auto* const pContainer = pDb->getContainer(keyContainer);
    if ( ! pContainer)
    {
        return false;
    }
    return (pContainer->getObject(keyObject));
}

CNode* CPointersClassic::getSiblingByKey(CNode* pNodeStart, const CNodeKey& siblingKey)
{
    if ( ! pNodeStart)
    {
        return {};
    }
    auto* const pParent = pNodeStart->getParent();
    if ( ! pParent)
    {
        return {};
    }
    return pParent->getChild(siblingKey);
}

std::optional<int> CPointersClassic::getNodeNumericValue(CNode* pNode)
{
    if ( ! pNode)
    {
        return {};
    }
    auto content = pNode->getContent();
    if ( ! std::holds_alternative<int>(content))
    {
        return {};
    }
    return std::get<int>(content);
}

std::optional<int> CPointersClassic::getSiblingValueSquared(CNode* pNodeStart, const CNodeKey& siblingKey)
{
    // auto* pSibling = getSiblingByKey(pNodeStart, siblingKey);
    // return getNodeNumericValue(pSibling).transform(makeSquared);
    if ( ! pNodeStart)
    {
        return {};
    }
    auto* const pParent = pNodeStart->getParent();
    if ( ! pParent)
    {
        return {};
    }
    auto* const pSibling = pParent->getChild(siblingKey);
    auto oNumericValue = getNodeNumericValue(pSibling);
    return oNumericValue.transform(makeSquared);
}

int CPointersClassic::makeSquared(const int value)
{
    return value*value;
}

void CPointersClassic::testObjectValid()
{
    auto db = CDatabase::createTestDb();

    // OK Case
    {
        CContainerKey containerKey{3};
        CObjectKey objectKey{1};
        printlnWrapper("ContainerKey: {:} ObjectKey: {:} Exists: {:}",
                     static_cast<int>(containerKey),
                     static_cast<int>(objectKey),
                     isObjectValid(&db, containerKey, objectKey));
    }

    // NOK Case
    {
        CContainerKey containerKey{8};
        CObjectKey objectKey{2};
        printlnWrapper("ContainerKey: {:} ObjectKey: {:} Exists: {:}",
                     static_cast<int>(containerKey),
                     static_cast<int>(objectKey),
                     isObjectValid(&db, containerKey, objectKey));
    }

}

void CPointersClassic::testNodeSiblingValueSquared()
{
    auto pTreeRoot = createTestTree();
    // OK Case
    {
        auto* pNodeStart = pTreeRoot->getChild(CNodeKey(3));
        auto oResult = CPointersClassic::getSiblingValueSquared(pNodeStart,CNodeKey(2));
        printlnWrapper("Is value: {:} Value {:}",oResult.has_value(),oResult.value_or(0));
    }

    // NOK Case
    {
        auto* pNodeStart = pTreeRoot->getChild(CNodeKey(3));
        auto oResult = CPointersClassic::getSiblingValueSquared(pNodeStart,CNodeKey(42));
        printlnWrapper("Is value: {:} Value {:}",oResult.has_value(),oResult.value_or(0));
    }
}
