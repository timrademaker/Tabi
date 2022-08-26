#pragma once

#include "Enums/EController.h"
#include "Enums/EKeyboard.h"
#include "Enums/EMouse.h"

namespace tabi
{
    class IInputHandler
    {
        friend class InputManager;
        static IInputHandler* CreateInstance();

    public:
        virtual ~IInputHandler() = default;

        /**
         * @brief Update the input state
         */
        virtual void Update() = 0;

        /**
        * @brief Determines if any button is down
        * @returns True if any button is currently down
        */
        virtual bool AnyButtonDown() const = 0;

        /**
        * @brief Determines if a button is currently down
        * @param a_Button The button to check the state for
        * @param a_DownLastFrame Will be set to true if the button was down last frame (optional)
        * @returns True if the button is down
        */
        virtual bool IsButtonDown(EKeyboard a_Button, bool* a_DownLastFrame = nullptr) const = 0;
        virtual bool IsButtonDown(EController a_Button, bool* a_DownLastFrame = nullptr) const = 0;
        virtual bool IsButtonDown(EMouse a_Button, bool* a_DownLastFrame = nullptr) const = 0;

        /**
        * @brief Gets the axis value of an axis
        * @param a_Axis The axis to retrieve the axis value for
        * @param a_Delta Will be filled with the axis delta compared to last frame (optional)
        * @returns The axis value
        */
        virtual float GetAxisValue(EController a_Axis, float* a_Delta = nullptr) const = 0;
        virtual float GetAxisValue(EMouse a_Axis, float* a_Delta = nullptr) const = 0;

        /**
        * @brief Show or hide the mouse cursor
        * @param a_Visible Whether the mouse cursor should be visible or not
        */
        virtual void SetMouseCursorVisible(bool a_Visible) { }

        /**
        * @brief Enable or disable mouse cursor capture
        * @param a_Capture Whether the mouse cursor should be captured or not
        */
        virtual void SetMouseCursorCapture(bool a_Capture) { }

        /**
         * @brief Handle a platform-specific window message
         * @param a_Msg The message to handle
         */
        virtual void HandleWindowMsg(const void* a_Msg) { }

    protected:
        IInputHandler() = default;
    };

}
