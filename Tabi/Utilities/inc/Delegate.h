#pragma once

#include <functional>

#include <TabiTypes.h>

#define DECLARE_DELEGATE(DelegateName, ...) \
    using DelegateName = tabi::DelegateBase<__VA_ARGS__>;

namespace tabi
{
    template<typename... DelegateArgs>
    class DelegateBase
    {
        using DelegateType = std::function<void(DelegateArgs...)>;
    public:
        DelegateBase() = default;
        ~DelegateBase() = default;

        void Add(DelegateType a_Func);
        void Remove(DelegateType a_Func);
        void RemoveAll();

        void Broadcast(DelegateArgs... a_Args);

    private:
        // Alternatively, make this a multimap/set so that an entire object can be unsubbed at once (and to make Remove easier to make).
        tabi::vector<DelegateType> m_Delegates;

    };


    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Add(DelegateType a_Func)
    {
        m_Delegates.push_back(a_Func);
    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Remove(DelegateType a_Func)
    {
        for (std::size_t i = 0; i < m_Delegates.size(); ++i)
        {
            //if (m_Delegates[i] == a_Func)
            //{
            //    m_Delegates.erase(m_Delegates.begin() + i);
            //    return;
            //}
        }
    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::RemoveAll()
    {
        m_Delegates.clear();
    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Broadcast(DelegateArgs ...a_Args)
    {
        for (DelegateType& d : m_Delegates)
        {
            d(a_Args...);
        }
    }
}
