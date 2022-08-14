#pragma once

#include "IInputHandler.h"
#include "Enums/EInputDevice.h"

#include <TabiContainers.h>
#include <TabiEvent.h>

#include <functional>

namespace tabi
{
    enum class EMouse;
    enum class EKeyboard;
    enum class EController;

    struct ButtonDownEvent
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
        DECLARE_EVENT(ButtonDownCallbackEvent, ButtonDownEvent);
        DECLARE_EVENT(AxisCallbackEvent, AxisEvent);

        using ButtonDownHandlerSignature = ButtonDownCallbackEvent::CallbackType;
        using ButtonUpHandlerSignature = Event::CallbackType;

        struct ButtonCallbacks
        {
            ButtonDownCallbackEvent m_ButtonDownCallback;
            Event m_ButtonUpCallback;
        };

        using ButtonDownEventMap = tabi::unordered_map<unsigned int, ButtonCallbacks>;

        using AxisHandlerSignature = std::function<void(AxisEvent)>;
        using AxisEventMap = tabi::unordered_map<unsigned int, AxisCallbackEvent>;

        template<typename ButtonEnumType>
        struct is_button_type : std::bool_constant<std::is_same_v<ButtonEnumType, EController> || std::is_same_v<ButtonEnumType, EKeyboard> || std::is_same_v<ButtonEnumType, EMouse>> {};
        template<class ButtonEnumType>
        static inline constexpr bool is_button_type_v = is_button_type<ButtonEnumType>::value;

        template<typename AxisEnumType>
        struct is_axis_type : std::bool_constant<std::is_same_v<AxisEnumType, EController> || std::is_same_v<AxisEnumType, EMouse>> {};
        template<class AxisEnumType>
        static inline constexpr bool is_axis_type_v = is_button_type<AxisEnumType>::value;

    public:
        /**
        * @brief Bind an object to receive events if a specific button is pressed
        * @param a_Button The button the object should receive events for
        * @param a_Object The object that should receive events
        * @param a_ButtonDownCallback The function that should be called when the specified button is pressed
        * @param a_ButtonUpCallback The function that should be called when the specified button is released
        */
        template<typename UserClass>
        static void BindButton(EMouse a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)() = nullptr);
        template<typename UserClass>
        static void BindButton(EKeyboard a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)() = nullptr);
        template<typename UserClass>
        static void BindButton(EController a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)() = nullptr);

        /**
        * @brief Bind an object to receive events if a specific axis is moved
        * @param a_Axis The axis the object should receive events for
        * @param a_Object The object that should receive events
        * @param a_Callback The function that should be called when the specified axis is moved
        */
        template<typename UserClass>
        static void BindAxis(EMouse a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));
        template<typename UserClass>
        static void BindAxis(EKeyboard a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));
        template<typename UserClass>
        static void BindAxis(EController a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));

        /**
        * @brief Unbind a specific button for an object
        * @param a_Button The button to stop receiving events for
        * @param a_Object The object that should no longer receive input from the specified button
        */
        static void UnbindButton(EMouse a_Button, void* a_Object);
        static void UnbindButton(EKeyboard a_Button, void* a_Object);
        static void UnbindButton(EController a_Button, void* a_Object);
        /**
        * @brief Unbind a specific axis for an object
        * @param a_Axis The axis to stop receiving events for
        * @param a_Object The object that should no longer receive input from the specified axis
        */
        static void UnbindAxis(EMouse a_Axis, void* a_Object);
        static void UnbindAxis(EKeyboard a_Axis, void* a_Object);
        static void UnbindAxis(EController a_Axis, void* a_Object);

        /**
        * @brief Unbind all buttons for an object
        * @param a_Object The object that should no longer receive button input
        */
        static void UnbindAllButtons(void* a_Object);
        /**
        * @brief Unbind all axes for an object
        * @param a_Object The object that should no longer receive axis input
        */
        static void UnbindAllAxes(void* a_Object);

        /**
        * @brief Checks if any button is down
        * @returns True if any button is down
        */
        static bool AnyButtonDown();

        /**
        * @brief Determines if a button is currently down
        * @param a_Button The button to check the state for
        * @param a_DownLastFrame Will be set to true if the button was down last frame (optional)
        * @returns True if the button is down
        */
        template<typename ButtonEnumType>
        static std::enable_if_t<is_button_type_v<ButtonEnumType>, bool>
            IsButtonDown(ButtonEnumType a_Button, bool* a_DownLastFrame = nullptr);

        /**
        * @brief Gets the axis value of an axis
        * @param a_Axis The axis to retrieve the axis value for
        * @param a_Delta Will be filled with the axis delta compared to last frame (optional)
        * @returns The axis value
        */
        template<typename AxisEnumType>
        static std::enable_if_t<is_axis_type_v<AxisEnumType>, float>
            GetAxisValue(AxisEnumType a_Axis, float* a_Delta = nullptr);

        /**
        * @brief Determines if a button is currently down. Ignores input block state.
        * @param a_Button The button to check the state for
        * @param a_DownLastFrame Will be set to true if the button was down last frame (optional)
        * @returns True if the button is down
        */
        template<typename ButtonEnumType>
        static std::enable_if_t<is_button_type_v<ButtonEnumType>, bool>
            IsButtonDownRaw(ButtonEnumType a_Button, bool* a_DownLastFrame = nullptr);

        /**
        * @brief Gets the axis value of an axis. Ignores input block state.
        * @param a_Axis The axis to retrieve the axis value for
        * @param a_Delta Will be filled with the axis delta compared to last frame (optional)
        * @returns The axis value
        */
        template<typename AxisEnumType>
        static std::enable_if_t<is_axis_type_v<AxisEnumType>, float>
            GetAxisValueRaw(AxisEnumType a_Axis, float* a_Delta = nullptr);

        /**
         * @brief Disable input from a given device
         * @note Each call to this function should be matched by a call to UnblockInput
         */
        static void BlockInput(EInputDevice a_Device);

        /**
         * @brief Enable input from a given device
         * @note This function should be called once for every time BlockInput is called
         */
        static void UnblockInput(EInputDevice a_Device);

        /**
        * @brief Updates user input and calls callback functions if a button was pressed
        */
        static void Update();

        /**
        * @brief Sets the cursor's visibility
        * @param a_ShowCursor Whether the cursor should be visible while it is in the window or not
        */
        static void SetCursorVisible(bool a_ShowCursor);

        /**
        * @brief Confine the cursor to the window
        * @param a_Capture Whether the cursor should be captured or not
        */
        static void SetCursorCapture(bool a_Capture);

        /**
         * @brief Handle a platform-specific window message
         * @param a_Msg The message to handle
         */
        static void HandleWindowsMsg(const void* a_Msg);

    private:
        InputManager();
        ~InputManager();

        template<typename ButtonEnumType, typename UserClass>
        void BindButtonInternal(ButtonEnumType a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)());

        void UnbindButtonInternal(unsigned int a_Button, void* a_Object);
        void BindAxisInternal(unsigned int a_Axis, void* a_Object, AxisHandlerSignature a_Callback);
        void UnbindAxisInternal(unsigned int a_Axis, void* a_Object);

        template<typename ButtonEnumType>
        static std::enable_if_t<is_button_type_v<ButtonEnumType> || is_axis_type_v<ButtonEnumType>, bool>
            IsInputBlocked();

        static EInputDevice DetermineDeviceType(unsigned int a_Button);

        template<typename ButtonEnumType>
        static constexpr std::enable_if_t<is_button_type_v<ButtonEnumType> || is_axis_type_v<ButtonEnumType>, EInputDevice>
            DetermineDeviceType();

        static InputManager& GetInstance(); // Used for the internal instance

    private:
        ButtonDownEventMap m_BoundButtons;
        AxisEventMap m_BoundAxes;

        IInputHandler* m_InputHandler;

        // Used to track how often input was blocked for a given device
        tabi::map<EInputDevice, int32_t> m_InputBlockCount;
    };

    template<typename UserClass>
    inline void InputManager::BindButton(EMouse a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        GetInstance().BindButtonInternal(a_Button, a_Object, a_ButtonDownCallback, a_ButtonUpCallback);
    }

    template<typename UserClass>
    inline void InputManager::BindButton(EKeyboard a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        GetInstance().BindButtonInternal(a_Button, a_Object, a_ButtonDownCallback, a_ButtonUpCallback);
    }

    template<typename UserClass>
    inline void InputManager::BindButton(EController a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        GetInstance().BindButtonInternal(a_Button, a_Object, a_ButtonDownCallback, a_ButtonUpCallback);
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

    template <typename ButtonEnumType>
    std::enable_if_t<InputManager::is_button_type_v<ButtonEnumType>, bool>
        InputManager::IsButtonDown(ButtonEnumType a_Button, bool* a_DownLastFrame)
    {
        if (!IsInputBlocked<ButtonEnumType>())
        {
            return IsButtonDownRaw(a_Button, a_DownLastFrame);
        }

        return false;
    }

    template <typename AxisEnumType>
    std::enable_if_t<InputManager::is_axis_type_v<AxisEnumType>, float>
        InputManager::GetAxisValue(AxisEnumType a_Axis, float* a_Delta)
    {
        if (!IsInputBlocked<AxisEnumType>())
        {
            return GetAxisValueRaw(a_Axis, a_Delta);
        }

        return 0.0f;
    }

    template <typename ButtonEnumType>
    std::enable_if_t<InputManager::is_button_type_v<ButtonEnumType>, bool>
    InputManager::IsButtonDownRaw(ButtonEnumType a_Button, bool* a_DownLastFrame)
    {
        return GetInstance().m_InputHandler->IsButtonDown(a_Button, a_DownLastFrame);
    }

    template <typename AxisEnumType>
    std::enable_if_t<InputManager::is_axis_type_v<AxisEnumType>, float>
    InputManager::GetAxisValueRaw(AxisEnumType a_Axis, float* a_Delta)
    {
        return GetInstance().m_InputHandler->GetAxisValue(a_Axis, a_Delta);
    }

    template <typename ButtonEnumType>
    std::enable_if_t<InputManager::is_button_type_v<ButtonEnumType> || InputManager::is_axis_type_v<ButtonEnumType>, bool>
        InputManager::IsInputBlocked()
    {
        const EInputDevice inputDevice = DetermineDeviceType<ButtonEnumType>();
        return GetInstance().m_InputBlockCount[inputDevice] > 0;
    }

    template <typename ButtonEnumType>
    constexpr std::enable_if_t<InputManager::is_button_type_v<ButtonEnumType> || InputManager::is_axis_type_v<ButtonEnumType>, EInputDevice>
        InputManager::DetermineDeviceType()
    {
        if constexpr (std::is_same_v<ButtonEnumType, EController>)
        {
            return EInputDevice::Controller;
        }
        else if constexpr (std::is_same_v<ButtonEnumType, EKeyboard>)
        {
            return EInputDevice::Keyboard;
        }
        else if constexpr (std::is_same_v<ButtonEnumType, EMouse>)
        {
            return EInputDevice::Mouse;
        }
        else
        {
            static_assert(!std::is_same_v<ButtonEnumType, ButtonEnumType>, "Unknown button type");
            return static_cast<EInputDevice>(-1);
        }
    }

    template <typename ButtonEnumType, typename UserClass>
    void InputManager::BindButtonInternal(ButtonEnumType a_Button, UserClass* a_Object,
        void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        if (a_ButtonDownCallback)
        {
            const ButtonDownHandlerSignature buttonDownFunc = std::bind(a_ButtonDownCallback, a_Object, std::placeholders::_1);
            m_BoundButtons[static_cast<unsigned>(a_Button)].m_ButtonDownCallback.Subscribe(a_Object, buttonDownFunc);
        }

        if (a_ButtonUpCallback)
        {
            const ButtonUpHandlerSignature buttonUpFunc = std::bind(a_ButtonUpCallback, a_Object);
            m_BoundButtons[static_cast<unsigned>(a_Button)].m_ButtonUpCallback.Subscribe(a_Object, buttonUpFunc);
        }
    }
}
