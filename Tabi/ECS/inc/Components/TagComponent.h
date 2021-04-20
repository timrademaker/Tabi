#pragma once

#include <TabiContainers.h>
#include <TabiMacros.h>


namespace tabi
{
    class TagComponent
    {
    public:
        TABI_INLINE bool HasTag(const tabi::string& a_Tag) const
        {
            return m_Tags.find(a_Tag) != m_Tags.end();
        }

        TABI_INLINE void AddTag(const tabi::string& a_Tag)
        {
            m_Tags.insert(a_Tag);
        }

    private:
        tabi::set<tabi::string> m_Tags;
    };
}
