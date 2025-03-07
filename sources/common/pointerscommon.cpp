#include "pointerscommon.h"

CNode::CNode(const CNodeKey& key, const CContent& content)
    : m_Key(key),
      m_Content(content)
{
}

CNodeKey CNode::getKey() const
{
    return m_Key;
}

CNode* CNode::getParent()
{
    return m_pParent;
}

CNode* CNode::getChild(const CNodeKey nodeKey)
{
    auto iter = m_Children.find(nodeKey);
    if (iter == m_Children.end())
    {
        return {};
    }
    return iter->second.get();
}

CNode* CNode::createChild(const CNodeKey& key, const CContent& childContent)
{
    auto pOwnedChild = std::make_unique<CNode>(key,childContent);
    pOwnedChild->m_pParent = this;
    CNode* pChild = pOwnedChild.get();
    m_Children.emplace(std::make_pair(key,std::move(pOwnedChild)));
    return pChild;
}

CContent CNode::getContent() const
{
    return m_Content;
}

void CNode::setContent(const CContent& arg)
{
    m_Content = arg;
}

std::unique_ptr<CNode> createTestTree()
{
    auto pRoot = std::make_unique<CNode>(CNodeKey(0));
    auto* const pChild01 = pRoot->createChild(CNodeKey(1),"Abc");
    auto* const pChild02 = pRoot->createChild(CNodeKey(2),22);
    auto* const pChild03 = pRoot->createChild(CNodeKey(3),33);

    pChild01->createChild(CNodeKey(11),"!!!");
    pChild01->createChild(CNodeKey(12),1212);

    pChild02->createChild(CNodeKey(21),"Xyz");

    pChild03->createChild(CNodeKey(31),"???");

    return pRoot;
}



CObject* CContainer::getObject(const CObjectKey& key)
{
    const auto it = m_Objects.find(key);
    if (it == m_Objects.end())
    {
        return {};
    }
    return it->second.get();
}

CContainer CContainer::createTestContainer()
{
    CContainer cnt;
    cnt.m_Objects.emplace(std::make_pair(CObjectKey{1},std::make_unique<CObject>()));
    cnt.m_Objects.emplace(std::make_pair(CObjectKey{3},std::make_unique<CObject>()));
    cnt.m_Objects.emplace(std::make_pair(CObjectKey{7},std::make_unique<CObject>()));
    return cnt;
}

CContainer* CDatabase::getContainer(const CContainerKey& key)
{
    const auto it = m_Containers.find(key);
    if (it == m_Containers.end())
    {
        return {};
    }
    return it->second.get();
}

CDatabase CDatabase::createTestDb()
{
    CDatabase db;

    db.m_Containers.emplace(std::make_pair(CContainerKey{1},std::make_unique<CContainer>(CContainer::createTestContainer())));
    db.m_Containers.emplace(std::make_pair(CContainerKey{3},std::make_unique<CContainer>(CContainer::createTestContainer())));
    db.m_Containers.emplace(std::make_pair(CContainerKey{7},std::make_unique<CContainer>()));

    return db;
}


