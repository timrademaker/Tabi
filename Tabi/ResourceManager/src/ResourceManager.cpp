#include "ResourceManager.h"

using namespace tabi;

ResourceManager& tabi::ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

tabi::string tabi::ResourceManager::GetPath(const tabi::string& a_Path) const
{
    tabi::string fullPath = a_Path;

    for (const auto& wCard : m_Wildcards)
    {
        if (fullPath.find(wCard.first) != tabi::string::npos)
        {
            fullPath = StringReplace(fullPath, wCard.first, wCard.second);
        }
    }

    return fullPath;
}

void tabi::ResourceManager::AddWildcard(const tabi::string& a_Wildcard, const tabi::string& a_Value)
{
    for (auto iter = m_Wildcards.begin(); iter != m_Wildcards.end(); ++iter)
    {
        if (iter->first == a_Wildcard)
        {
            m_Wildcards.erase(iter);
            break;
        }
    }

    m_Wildcards.push_back(tabi::make_pair(a_Wildcard, a_Value));

}