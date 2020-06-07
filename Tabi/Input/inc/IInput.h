#pragma once

namespace tabi
{
    // TODO: Move to another file (and add buttons)
    // If enums for different devices are put in different ranges (with flags?), the device can automatically be deducted.
    enum class EKeyboard : unsigned int
    { };

    class IInput
    {
        typedef void (*ButtonHandlerSignature)(bool a_First);
        typedef void (*AxisHandlerSignature)(float a_AxisValue, float a_Delta);

        using Button = unsigned int;
        using Axis = unsigned int;
    public:
        static IInput& GetInstance();

        template<class UserClass>
        static void BindButton(Button a_Button, UserClass* a_Object, ButtonHandlerSignature a_Callback);
        template<class UserClass>
        static void BindAxis(Axis a_Axis, UserClass* a_Object, AxisHandlerSignature a_Callback);

        template<class UserClass>
        static void UnbindButton(Button a_Button, UserClass* a_Object);
        template<class UserClass>
        static void UnbindAxis(Axis a_Axis, UserClass* a_Object);

        template<class UserClass>
        static void UnbindAllButtons(UserClass* a_Object);

        template<class UserClass>
        static void UnbindAllAxes(UserClass* a_Object);


        virtual bool AnyButtonDown() = 0;

        virtual void Update() = 0;
        // No virtual function to handle messages - this could differ per platform. Application should deal with making sure the correct function is called, with the correct arguments.

    protected:
        IInput() = default;
        ~IInput() = default;

        template<class UserClass>
        virtual void BindButton_Impl(Button a_Button, UserClass* a_Object, ButtonHandlerSignature a_Callback) = 0;
        template<class UserClass>
        virtual void BindAxis_Impl(Axis a_Axis, UserClass* a_Object, AxisHandlerSignature a_Callback) = 0;

        template<class UserClass>
        virtual void UnbindButton_Impl(Button a_Button, UserClass* a_Object) = 0;
        template<class UserClass>
        virtual void UnbindAxis_Impl(Axis a_Axis, UserClass* a_Object) = 0;

        template<class UserClass>
        virtual void UnbindAllButtons_Impl(UserClass* a_Object) = 0;

        template<class UserClass>
        virtual void UnbindAllAxes_Impl(UserClass* a_Object) = 0;


        virtual bool AnyButoonDown_Impl() = 0;
    };

}