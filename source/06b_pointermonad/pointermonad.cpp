#include "pointermonad.h"
#include "../common/printutils.h"
#include <functional>

bool CPointerMonad::isObjectValid(CPtr<CDatabase*> pDb, const CContainerKey keyContainer, const CObjectKey keyObject)
{
    return (pDb.and_then(&CDatabase::getContainer,keyContainer)
               .and_then(&CContainer::getObject, keyObject));
}

CNode* CPointerMonad::getNodeParent(CNode& node)
{
    return node.getParent();
}

CNode* CPointerMonad::getNodeChild(CNode& parent, const CNodeKey& childKey)
{
    return parent.getChild(childKey);
}

CContent CPointerMonad::getNodeContent(CNode& node)
{
    return node.getContent();
}

std::optional<int> CPointerMonad::getContentNumericValue(const CContent& content)
{
    if ( ! std::holds_alternative<int>(content))
    {
        return {};
    }
    return std::get<int>(content);
}

std::optional<int> CPointerMonad::getNodeNumericValue(CNode& node)
{
    return getContentNumericValue(node.getContent());
}

std::optional<int> CPointerMonad::getSiblingValueSquared(CNode* pNodeStart, const CNodeKey& siblingKey)
{
    return CPtr(pNodeStart)
        .and_then(std::mem_fn(&CNode::getParent))
        .and_then(std::mem_fn(&CNode::getChild),siblingKey)
        .and_then(getNodeNumericValue)
        .transform(makeSquared);
}

int CPointerMonad::makeSquared(const int value)
{
    return value*value;
}

void CPointerMonad::testObjectValid()
{
    auto db = CDatabase::createTestDb();
    auto pDb = CPtr(&db);

    // OK Case
    {
        CContainerKey containerKey{3};
        CObjectKey objectKey{1};
        printlnWrapper("ContainerKey: {:} ObjectKey: {:} Exists: {:}",
                     static_cast<int>(containerKey),
                     static_cast<int>(objectKey),
                     isObjectValid(pDb, containerKey, objectKey));
    }

    // NOK Case
    {
        CContainerKey containerKey{8};
        CObjectKey objectKey{2};
        printlnWrapper("ContainerKey: {:} ObjectKey: {:} Exists: {:}",
                     static_cast<int>(containerKey),
                     static_cast<int>(objectKey),
                     isObjectValid(pDb, containerKey, objectKey));
    }
}

void CPointerMonad::testNodeSiblingValueSquared()
{
    auto pTreeRoot = createTestTree();
    // OK Case
    {
        auto* pNodeStart = pTreeRoot->getChild(CNodeKey(3));
        auto oResult = CPointerMonad::getSiblingValueSquared(pNodeStart,CNodeKey(2));
        printlnWrapper("Is value: {:} Value {:}",oResult.has_value(),oResult.value_or(0));
    }

    // NOK Case
    {
        auto* pNodeStart = pTreeRoot->getChild(CNodeKey(3));
        auto oResult = CPointerMonad::getSiblingValueSquared(pNodeStart,CNodeKey(42));
        printlnWrapper("Is value: {:} Value {:}",oResult.has_value(),oResult.value_or(0));
    }}
