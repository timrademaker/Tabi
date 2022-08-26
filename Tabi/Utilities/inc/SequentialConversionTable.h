#pragma once

#include <TabiContainers.h>
#include <TabiMacros.h>

#include <cstdint>

namespace tabi
{
    /**
     * @brief A class that allows conversion between keys and values for a sequential range of keys (e.g. enums)
     */
    template<typename KeyType, typename ValueType, KeyType FirstEntry, KeyType LastEntry>
    class SequentialConversionTable
    {
    public:
        const ValueType& Get(uint32_t a_KeyIndex) const
        {
            TABI_ASSERT(a_KeyIndex < m_NumEntries);

            return m_Table[a_KeyIndex];
        }

        const ValueType& Get(KeyType a_Key) const
        {
            TABI_ASSERT(static_cast<int64_t>(a_Key) - m_FirstEntryValue < m_NumEntries);

            return m_Table[static_cast<int64_t>(a_Key) - m_FirstEntryValue];
        }
        

    protected:
        SequentialConversionTable()
            : SequentialConversionTable(static_cast<ValueType>(-1))
        { }

        SequentialConversionTable(ValueType a_InvalidEntry)
            : m_InvalidEntry(a_InvalidEntry)
        {
            static_assert(static_cast<int64_t>(LastEntry) - static_cast<int64_t>(FirstEntry) + 1 <= UINT32_MAX, "Entry range too big for the table!");

            for (uint32_t i = 0; i < m_NumEntries; ++i)
            {
                m_Table[i] = m_InvalidEntry;
            }
        }

        void Add(KeyType a_Key, ValueType a_Value)
        {
            TABI_ASSERT(static_cast<int64_t>(a_Key) - m_FirstEntryValue < m_NumEntries);

            m_Table[static_cast<int64_t>(a_Key) - m_FirstEntryValue] = a_Value;
        }

    public:
        const int64_t m_FirstEntryValue = static_cast<int64_t>(FirstEntry);
        const uint32_t m_NumEntries = static_cast<int64_t>(LastEntry) - static_cast<int64_t>(FirstEntry) + 1;

        const ValueType m_InvalidEntry = static_cast<ValueType>(-1);

    private:
        tabi::array<ValueType, static_cast<int64_t>(LastEntry) - static_cast<int64_t>(FirstEntry) + 1> m_Table;
    };
}