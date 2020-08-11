#pragma once

#include <TabiTypes.h>

#include <functional>

#define DECLARE_DELEGATE(DelegateName, ...) \
    using DelegateName = tabi::DelegateBase<__VA_ARGS__>;

/**
* @brief Helper macros to subscribe to events
* @params Subscriber The object subscribing to the event
* @params Callback The callback function to send events to
*/
#define Subscribe(Subscriber, Callback)             Add(&Subscriber, std::bind(&Callback, &Subscriber))
#define Subscribe_OneParam(Subscriber, Callback)    Add(&Subscriber, std::bind(&Callback, &Subscriber, std::placeholders::_1))
#define Subscribe_TwoParams(Subscriber, Callback)   Add(&Subscriber, std::bind(&Callback, &Subscriber, std::placeholders::_1, std::placeholders::_2))
#define Subscribe_ThreeParams(Subscriber, Callback) Add(&Subscriber, std::bind(&Callback, &Subscriber, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
#define Subscribe_FourParams(Subscriber, Callback)  Add(&Subscriber, std::bind(&Callback, &Subscriber, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4))
#define Subscribe_FiveParams(Subscriber, Callback)  Add(&Subscriber, std::bind(&Callback, &Subscriber, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5))
#define Subscribe_SixParams(Subscriber, Callback)   Add(&Subscriber, std::bind(&Callback, &Subscriber, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6))

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

        /**
        * @brief Subscribe an object to an event
        * @params a_Object The object subscribing to the event
        * @params a_Callback The callback function to send events to
        */
        void Add(UserClass* a_Object, DelegateType a_Callback);
        /**
        * @brief Subscribe a static function to an event
        * @params a_Callback The callback function to send events to
        */
        void AddStatic(DelegateType a_Callback);
        /**
        * @brief Unsubscribes an object from events
        * @params a_Object The object to unsubscribe
        */
        void Remove(UserClass* a_Object);
        /**
        * @brief Removes all static subscribers
        */
        void RemoveStatic();
        /**
        * @brief Removes all subscribers
        */
        void RemoveAll();

        /**
        * @brief Broadcasts an event to all subscribers
        * @params a_Args The values sent to all subscribers' callback functions
        */
        void Broadcast(DelegateArgs... a_Args);

    private:
        DelegateMap m_Delegates;

    };


    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::Add(UserClass* a_Object, DelegateType a_Callback)
    {
        if (a_Callback)
        {
            m_Delegates[a_Object].push_back(a_Callback);
        }
#if defined(_DEBUG)
        else
        {
            tabi::logger::TabiWarn("[Delegate] Trying to add a callback that isn't valid!");
        }
#endif

    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::AddStatic(DelegateType a_Callback)
    {
        return Add(nullptr, a_Callback);
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
            tabi::logger::TabiWarn("Tried to unbind all delegates from an object, but nothing was bound!");
        }
#endif
    }

    template<typename ...DelegateArgs>
    inline void DelegateBase<DelegateArgs...>::RemoveStatic()
    {
        return Remove(nullptr);
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
