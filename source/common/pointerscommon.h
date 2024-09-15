#ifndef POINTERSCOMMON_H
#define POINTERSCOMMON_H

#include <unordered_map>
#include <memory>
#include <string>
#include <variant>

enum class CNodeKey : int;

using CContent = std::variant<std::monostate,
                              int,
                              std::string>;

class CNode
{
public:
    explicit CNode(const CNodeKey& key,
                   const CContent& content = {});

    CNodeKey getKey() const;
    CNode* getParent();
    CNode* getChild(const CNodeKey nodeKey);

    CNode* createChild(const CNodeKey& key,
                       const CContent& childContent = {});

    CContent getContent() const;
    void setContent(const CContent& arg);
private:
    CNodeKey m_Key{};
    CNode* m_pParent{};
    std::unordered_map<CNodeKey, std::unique_ptr<CNode>> m_Children{};
    CContent m_Content;
};


std::unique_ptr<CNode> createTestTree();


enum class CObjectKey : int;
enum class CContainerKey : int;

class CObject
{
};


class CContainer
{
public:
    CObject* getObject(const CObjectKey& key);

    static CContainer createTestContainer();
private:
    std::unordered_map<CObjectKey,std::unique_ptr<CObject>> m_Objects;
};

class CDatabase
{
public:
    CContainer* getContainer(const CContainerKey& key);

    static CDatabase createTestDb();
private:
    std::unordered_map<CContainerKey,std::unique_ptr<CContainer>> m_Containers;
};

#endif // POINTERSCOMMON_H
