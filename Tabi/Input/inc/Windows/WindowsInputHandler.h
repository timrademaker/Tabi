#pragma once

#include "IInputHandler.h"

#include <TabiContainers.h>

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_ALL_WARNINGS
#include <gainput/gainput.h>
#include <gainput/GainputInputManager.h>
#include <gainput/GainputInputMap.h>
DISABLE_WARNING_POP

namespace tabi
{
    enum class EMouse;
    enum class EKeyboard;
    enum class EController;
    enum class EInputDevice;
    

    class InputHandler : public IInputHandler
    {
    public:
        InputHandler();
        virtual ~InputHandler() = default;

        virtual void Update() override;

        virtual void BindButton(unsigned int a_Button) override;
        virtual void BindAxis(unsigned int a_Axis) override;

        // Determine device type internally
        virtual bool IsButtonDown(unsigned int a_Button) override;

        virtual float GetAxisValue(unsigned int a_Axis) override;

        void HandleMsg(const MSG& a_Msg);


    private:
        static unsigned int ConvertButton(unsigned int a_Button);
        static unsigned int ConvertButton(EMouse a_Button);
        static unsigned int ConvertButton(EKeyboard a_Button);
        static unsigned int ConvertButton(EController a_Button);
        
        unsigned int ConvertDeviceType(EInputDevice a_Device);

        static EInputDevice DetermineDeviceType(unsigned int a_Button);

        bool IsBound(unsigned int a_Button);

    private:

        static tabi::unordered_map<EMouse, unsigned int> ms_MouseTable;
        static tabi::unordered_map<EKeyboard, unsigned int> ms_KeyboardTable;
        static tabi::unordered_map<EController, unsigned int> ms_ControllerTable;

        tabi::unordered_map<EInputDevice, unsigned int> m_InputDeviceTable;

        ::gainput::InputManager m_GaInputManager;
        ::gainput::InputMap m_InputMap;
    };
}