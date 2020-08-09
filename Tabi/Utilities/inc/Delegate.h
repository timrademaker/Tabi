#pragma once

#include <TabiTypes.h>

#include <functional>

#define DECLARE_DELEGATE(DelegateName, ...) \
    using DelegateName = tabi::DelegateBase<__VA_ARGS__>;

namespace tabi
{
    template<typename... DelegateArgs>
    class DelegateBase
    {
        using UserClass = void;

        using DelegateType = std::function<void(DelegateArgs...)>;
        using DelegateMap = tabi::unordered_map<UserClass*, tabi::vector<DelegateType>>;
    public:
        DelegateBase() = default;
        ~DelegateBase() = default;

        void Add(UserClass* a_Object, DelegateType a_Func);
        void Remove(UserClass* a_Object);
        void RemoveAll();

        void Broadcast(DelegateArgs... a_Args);

    private:
        DelegateMap m_Delegates;

    };


    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Add(UserClass* a_Object, DelegateType a_Func)
    {
        m_Delegates[a_Object].push_back(a_Func);
    }


    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Remove(UserClass* a_Object)
    {
        auto iter = m_Delegates.find(a_Object);
        if (iter != m_Delegates.end())
        {
            m_Delegates.erase(iter);
        }
#if defined(_DEBUG)
        else
        {
            tabi::logger::TabiWarn("Tried to unbind a delegate, but nothing was bound!");
        }
#endif
    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::RemoveAll()
    {
        m_Delegates.clear();
    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Broadcast(DelegateArgs ...a_Args)
    {
        for (auto iter = m_Delegates.begin(); iter != m_Delegates.end(); ++iter)
        {
            for (DelegateType& d : iter->second)
            {
                d(a_Args...);
            }
        }
    }
}
