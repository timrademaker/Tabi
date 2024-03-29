#pragma once

#include <TabiMacros.h>
#include <TabiTypes.h>
#include <Logging.h>

#include <functional>

#define DECLARE_EVENT(EventName, EventInfoClass) \
    using EventName = tabi::EventBase<EventInfoClass>


namespace tabi
{
    using EmptyEvent = void;

    template<typename EventInfo>
    class EventBase
    {
    public:
        typedef std::conditional_t<std::is_same<EventInfo, EmptyEvent>::value, std::function<void()>, std::function<void(EventInfo)>> CallbackType;

    private:
        using CallbackMap = tabi::unordered_map<void*, tabi::vector<CallbackType>>;

    public:
        EventBase() = default;
        ~EventBase() = default;

        /**
        * @brief Subscribe a callback to an event
        * @param a_Object The object subscribing to the event
        * @param a_Callback The callback function to send events to
        */
        template<typename UserClass, typename T = EventInfo>
        typename std::enable_if<!std::is_same<T, tabi::EmptyEvent>::value, void>::type 
            Subscribe(UserClass* a_Object, void(UserClass::* a_Callback)(EventInfo)) const;
        /**
        * @brief Subscribe an object's callback to an event
        * @param a_Object The object subscribing to the event
        * @param a_Callback The callback function to send events to
        */
        template<typename UserClass, typename T = EventInfo>
        typename std::enable_if<std::is_same<T, tabi::EmptyEvent>::value, void>::type 
            Subscribe(UserClass* a_Object, void(UserClass::* a_Callback)()) const;

        /**
        * @brief Subscribe a callback to an event
        * @param a_Object The object subscribing to the event
        * @param a_Callback The callback function to send events to
        */
        void Subscribe(void* a_Object, CallbackType a_Callback) const;

        /**
        * @brief Subscribe a static function to an event
        * @param a_Callback The callback function to send events to
        */
        void SubscribeStatic(CallbackType a_Callback) const;
        /**
        * @brief Unsubscribes an object from events
        * @param a_Object The object to unsubscribe
        * @returns True if any callback was removed, false if none were found
        */
        bool Unsubscribe(void* a_Object) const;
        /**
        * @brief Removes all static subscribers
        * @returns True if any callback was removed, false if none were found
        */
        bool UnsubscribeStatic();
        /**
        * @brief Removes all subscribers
        */
        void UnsubscribeAll();

        /**
        * @brief Broadcasts an event to all subscribers
        * @param a_Event The message sent to all subscribers' callback functions
        */
        template<typename T = EventInfo>
        typename std::enable_if<!std::is_same<T, tabi::EmptyEvent>::value, void>::type Broadcast(EventInfo);
        /**
        * @brief Broadcasts an event to all subscribers. Only available when using tabi::Event
        */
        template<typename T = EventInfo>
        typename std::enable_if<std::is_same<T, tabi::EmptyEvent>::value, void>::type Broadcast();

        /**
        * @brief Checks if this event has any subscribers
        * @returns True if this event has any subscribers
        */
        bool HasSubscribers() const;

    private:
        /**
        * @brief Internal function that stores callbacks
        * @param a_Object The object subscribing to the event
        * @param a_Callback The callback function to send events to
        */
        void Subscribe_Internal(void* a_Object, CallbackType a_Callback) const;

    private:
        mutable CallbackMap m_Callbacks;
    };

    template<typename EventInfo>
    template<typename UserClass, typename T>
    inline typename std::enable_if<!std::is_same<T, tabi::EmptyEvent>::value, void>::type tabi::EventBase<EventInfo>::Subscribe(UserClass* a_Object, void(UserClass::* a_Callback)(EventInfo)) const
    {
        TABI_ASSERT(a_Object);
        TABI_ASSERT(a_Callback);
    
        auto bound = std::bind(a_Callback, a_Object, std::placeholders::_1);
        Subscribe_Internal(a_Object, bound);
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::Subscribe(void* a_Object, CallbackType a_Callback) const
    {
        Subscribe_Internal(a_Object, a_Callback);
    }

    template<typename EventInfo>
    template<typename UserClass, typename T>
    inline typename std::enable_if<std::is_same<T, tabi::EmptyEvent>::value, void>::type tabi::EventBase<EventInfo>::Subscribe(UserClass* a_Object, void(UserClass::* a_Callback)()) const
    {
        TABI_ASSERT(a_Object);
        TABI_ASSERT(a_Callback);

        auto bound = std::bind(a_Callback, a_Object);
        Subscribe_Internal(a_Object, bound);
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::SubscribeStatic(CallbackType a_Callback) const
    {
        return Subscribe_Internal(nullptr, a_Callback);
    }


    template<typename EventInfo>
    inline bool EventBase<EventInfo>::Unsubscribe(void* a_Object) const
    {
        auto iter = m_Callbacks.find(a_Object);
        if (iter != m_Callbacks.end())
        {
            m_Callbacks.erase(iter);
            return true;
        }
#if defined(_DEBUG)
        else
        {
            TABI_WARN("Tried to unsubscribe all delegates from an object, but nothing was bound!");
        }
#endif
        return false;
    }

    template<typename EventInfo>
    inline bool EventBase<EventInfo>::UnsubscribeStatic()
    {
        return Unsubscribe(nullptr);
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::UnsubscribeAll()
    {
        m_Callbacks.clear();
    }

    template<typename EventInfo>
    template<typename T>
    inline
        typename std::enable_if<!std::is_same<T, tabi::EmptyEvent>::value, void>::type EventBase<EventInfo>::Broadcast(EventInfo a_Event)
    {
        for (auto iter = m_Callbacks.begin(); iter != m_Callbacks.end(); ++iter)
        {
            for (CallbackType& d : iter->second)
            {
                d(a_Event);
            }
        }
    }

    template<typename EventInfo>
    template<typename T>
    inline
    typename std::enable_if<std::is_same<T, tabi::EmptyEvent>::value, void>::type EventBase<EventInfo>::Broadcast()
    {
        for (auto iter = m_Callbacks.begin(); iter != m_Callbacks.end(); ++iter)
        {
            for (CallbackType& d : iter->second)
            {
                d();
            }
        }
    }

    template<typename EventInfo>
    inline bool EventBase<EventInfo>::HasSubscribers() const
    {
        return m_Callbacks.size() > 0;
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::Subscribe_Internal(void* a_Object, CallbackType a_Callback) const
    {
        if (a_Callback)
        {
            m_Callbacks[a_Object].push_back(a_Callback);
        }
#if defined(_DEBUG)
        else
        {
            TABI_WARN("[TabiEvent] Trying to add a callback that isn't valid!");
        }
#endif
    }

    using Event = tabi::EventBase<EmptyEvent>;
}
