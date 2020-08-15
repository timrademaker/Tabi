#pragma once

#include <TabiTypes.h>

#include <functional>

#define DECLARE_DELEGATE(DelegateName, EventClass) \
    using DelegateName = tabi::DelegateBase<EventClass>

/**
* @brief Helper macros to subscribe to events
* @params Subscriber The object subscribing to the event
* @params Callback The callback function to send events to
*/
#define Subscribe(Subscriber, Callback)             Add(&Subscriber, std::bind(&Callback, Subscriber))
#define Subscribe_OneParam(Subscriber, Callback)    Add(&Subscriber, std::bind(&Callback, Subscriber, std::placeholders::_1))

namespace tabi
{
    template<typename EventInfo>
    class DelegateBase
    {
        using UserClass = void;

        using DelegateType = std::function<void(EventInfo)>;
        using DelegateMap = tabi::unordered_map<UserClass*, tabi::vector<DelegateType>>;
    public:
        DelegateBase() = default;
        ~DelegateBase() = default;

        /**
        * @brief Subscribe an object to an event. Note: It is easier to use the Subscribe-macro rather than this function directly
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
        * @params a_Event The message sent to all subscribers' callback functions
        */
        void Broadcast(EventInfo a_Event = {});

    private:
        DelegateMap m_Delegates;

    };


    template<typename EventInfo>
    inline void DelegateBase<EventInfo>::Add(UserClass* a_Object, DelegateType a_Callback)
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

    template<typename EventInfo>
    inline void DelegateBase<EventInfo>::AddStatic(DelegateType a_Callback)
    {
        return Add(nullptr, a_Callback);
    }


    template<typename EventInfo>
    inline void DelegateBase<EventInfo>::Remove(UserClass* a_Object)
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

    template<typename EventInfo>
    inline void DelegateBase<EventInfo>::RemoveStatic()
    {
        return Remove(nullptr);
    }

    template<typename EventInfo>
    inline void DelegateBase<EventInfo>::RemoveAll()
    {
        m_Delegates.clear();
    }

    template<typename EventInfo>
    inline void DelegateBase<EventInfo>::Broadcast(EventInfo a_Event)
    {
        for (auto iter = m_Delegates.begin(); iter != m_Delegates.end(); ++iter)
        {
            for (DelegateType& d : iter->second)
            {
                d(a_Event);
            }
        }
    }

    struct EmptyEvent {};
    using Delegate = tabi::DelegateBase<EmptyEvent>;    
}
