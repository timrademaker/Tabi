#pragma once

#include <TabiContainers.h>
#include <TabiEvent.h>

#include <functional>

namespace tabi
{
    enum class EMouse;
    enum class EKeyboard;
    enum class EController;

    struct ButtonEvent
    {
        /// True if the button went down between last frame and this frame
        bool m_FirstDown;
    };

    struct AxisEvent
    {
        /// The current position on the axis, in range [-1.0, 1.0]
        float m_AxisValue;
        /// The difference in position on the axis between the previous frame and this frame
        float m_Delta;
    };

    class InputManager
    {
        DECLARE_EVENT(ButtonCallbackEvent, ButtonEvent);
        DECLARE_EVENT(AxisCallbackEvent, AxisEvent);

        // TODO: Change the vector of pairs to a(n unordered) set (First test if this is slower, as iterating through a set is generally slower than through vectors)
        using ButtonHandlerSignature = std::function<void(ButtonEvent)>;
        using BoundButtonMap = tabi::unordered_map<unsigned int, ButtonCallbackEvent>;
        
        using AxisHandlerSignature = std::function<void(AxisEvent)>;
        using BoundAxesMap = tabi::unordered_map<unsigned int, AxisCallbackEvent>;

    public:
        /**
        * @brief Bind an object to receive events if a specific button is pressed
        * @params a_Button The button the object should receive events for
        * @params a_Object The object that should receive events
        * @params a_Callback The function that should be called when the specified button is pressed
        */
        template<typename UserClass>
        static void BindButton(EMouse a_Button, UserClass* a_Object, void(UserClass::* a_Callback)(ButtonEvent));
        template<typename UserClass>
        static void BindButton(EKeyboard a_Button, UserClass* a_Object, void(UserClass::* a_Callback)(ButtonEvent));
        template<typename UserClass>
        static void BindButton(EController a_Button, UserClass* a_Object, void(UserClass::* a_Callback)(ButtonEvent));

        /**
        * @brief Bind an object to receive events if a specific axis is moved
        * @params a_Axis The axis the object should receive events for
        * @params a_Object The object that should receive events
        * @params a_Callback The function that should be called when the specified axis is moved
        */
        template<typename UserClass>
        static void BindAxis(EMouse a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));
        template<typename UserClass>
        static void BindAxis(EKeyboard a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));
        template<typename UserClass>
        static void BindAxis(EController a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));

        /**
        * @brief Unbind a specific button for an object
        * @params a_Button The button to stop receiving events for
        * @params a_Object The object that should no longer receive input from the specified button
        */
        static void UnbindButton(EMouse a_Button, void* a_Object);
        static void UnbindButton(EKeyboard a_Button, void* a_Object);
        static void UnbindButton(EController a_Button, void* a_Object);
        /**
        * @brief Unbind a specific axis for an object
        * @params a_Button The axis to stop receiving events for
        * @params a_Object The object that should no longer receive input from the specified axis
        */
        static void UnbindAxis(EMouse a_Axis, void* a_Object);
        static void UnbindAxis(EKeyboard a_Axis, void* a_Object);
        static void UnbindAxis(EController a_Axis, void* a_Object);

        /**
        * @brief Unbind all buttons for an object
        * @params a_Object The object that should no longer receive button input
        */
        static void UnbindAllButtons(void* a_Object);
        /**
        * @brief Unbind all axes for an object
        * @params a_Object The object that should no longer receive axis input
        */
        static void UnbindAllAxes(void* a_Object);

        /**
        * @brief Checks if any button is down
        * @returns True if any button is down
        */
        static bool AnyButtonDown();

        /**
        * @brief Updates user input and calls callback functions if a button was pressed
        */
        static void Update();

        /**
        * @brief Sets the cursor's mode
        * @params a_Visible Whether the cursor should be visible while it is in the window or not
        * @params a_CaptureCursor Whether the cursor should be able to leave the window or not
        */
        static void SetCursorMode(bool a_Visible, bool a_CaptureCursor);

        /**
        * @brief Called internally when the window loses or regains focus
        */
        static void SetFocus(bool a_HasFocus);

    private:
        InputManager() = default;
        ~InputManager() = default;

        void BindButtonInternal(unsigned int a_Button, void* a_Object, ButtonHandlerSignature a_Callback);
        void UnbindButtonInternal(unsigned int a_Button, void* a_Object);
        void BindAxisInternal(unsigned int a_Axis, void* a_Object, AxisHandlerSignature a_Callback);
        void UnbindAxisInternal(unsigned int a_Axis, void* a_Object);

        static InputManager& GetInstance(); // Used for the internal instance

    private:
        BoundButtonMap m_BoundButtons;
        BoundAxesMap m_BoundAxes;
    };

    template<typename UserClass>
    inline void InputManager::BindButton(EMouse a_Button, UserClass* a_Object, void(UserClass::* a_Callback)(ButtonEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindButtonInternal(static_cast<unsigned>(a_Button), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindButton(EKeyboard a_Button, UserClass* a_Object, void(UserClass::* a_Callback)(ButtonEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindButtonInternal(static_cast<unsigned>(a_Button), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindButton(EController a_Button, UserClass* a_Object, void(UserClass::* a_Callback)(ButtonEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindButtonInternal(static_cast<unsigned>(a_Button), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindAxis(EMouse a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindAxis(EKeyboard a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindAxis(EController a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, boundFunction);
    }

}