#pragma once

namespace tabi
{
    class IInputHandler
    {
    public:
        static IInputHandler& GetInstance();

        // No virtual function to handle messages - this could differ per platform. Application should deal with making sure the correct function is called, with the correct arguments.
        virtual void Update() = 0;

        /**
        * @brief Binds a button in the input handler (i.e. makes sure the button state will be checked on update)
        * @params a_Button The button identifier of the button to bind
        */
        virtual void BindButton(unsigned int a_Button) = 0;
        /**
        * @brief Unbinds a button in the input handler (i.e. could make sure the button state is no longer checked on update)
        * @params a_Button The button identifier of the button to unbind
        */
        virtual void UnbindButton(unsigned int a_Button) = 0;
        /**
        * @brief Binds an axis in the input handler (i.e. makes sure the axis state will be checked on update)
        * @params a_Axis The axis identifier of the axis to bind
        */
        virtual void BindAxis(unsigned int a_Axis) = 0;
        /**
        * @brief Unbinds an axis in the input handler (i.e. could make sure the axis state is no longer checked on update)
        * @params a_Button The axis identifier of the axis to unbind
        */
        virtual void UnbindAxis(unsigned int a_Axis) = 0;

        /**
        * @brief Determines if a button is currently down
        * @params a_Button The button to check the state for
        * @params a_DownLastFrame Will be set to true if the button went down last frame (optional)
        * @returns True if the button is down
        */
        virtual bool IsButtonDown(unsigned int a_Button, bool* a_DownLastFrame = nullptr) = 0;

        /**
        * @brief Determines if any button is down
        * @returns True if any button is currently down
        */
        virtual bool AnyButtonDown() = 0;

        /**
        * @brief Gets the axis value of an axis
        * @params a_Axis The axis to retrieve the axis value for
        * @params a_Delta Will be filled with the axis delta compared to last frame (optional)
        * @returns The axis value
        */
        virtual float GetAxisValue(unsigned int a_Axis, float* a_Delta = nullptr) = 0;


        /**
        * @brief Show or hide the mouse cursor
        * @params a_Visible Whether the mouse cursor should be visible or not
        */
        virtual void SetMouseCursorVisible(bool a_Visible) = 0;

        /**
        * @brief Enable or disable mouse cursor capture
        * @params a_Capture Whether the mouse cursor should be captured or not
        */
        virtual void SetMouseCursorCapture(bool a_Capture) = 0;

    protected:
        IInputHandler() = default;
        ~IInputHandler() = default;
    };

}