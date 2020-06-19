#pragma once

namespace tabi
{
    class IInputHandler
    {
    public:
        static IInputHandler& GetInstance();

        // No virtual function to handle messages - this could differ per platform. Application should deal with making sure the correct function is called, with the correct arguments.

        virtual bool IsButtonDown(unsigned int a_Button) = 0;

        virtual float GetAxisValue(unsigned int a_Axis) = 0;

    protected:
        IInputHandler() = default;
        ~IInputHandler() = default;
    };

}