#pragma once

#include "IInputHandler.h"

#include <TabiContainers.h>
#include <TabiPlatform.h>

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
        virtual void UnbindButton(unsigned int a_Button) override;
        virtual void BindAxis(unsigned int a_Axis) override;
        virtual void UnbindAxis(unsigned int a_Axis) override;

        virtual bool IsButtonDown(unsigned int a_Button, bool* a_DownLastFrame = nullptr) override;

        virtual bool AnyButtonDown() override;

        virtual float GetAxisValue(unsigned int a_Axis, float* a_Delta = nullptr) override;

        virtual void SetMouseCursorVisible(bool a_Visible) override;
        virtual void SetMouseCursorCapture(bool a_Capture) override;
        
        
        void HandleMsg(const MSG& a_Msg);


    private:
        // Convert buttons to their internal equivalent (gainput)
        static unsigned int ConvertButton(unsigned int a_Button);
        static unsigned int ConvertButton(EMouse a_Button);
        static unsigned int ConvertButton(EKeyboard a_Button);
        static unsigned int ConvertButton(EController a_Button);
        
        // Convert device type to its internal equivalent (gainput)
        unsigned int ConvertDeviceType(EInputDevice a_Device);

        static EInputDevice DetermineDeviceType(unsigned int a_Button);

        bool IsBound(unsigned int a_Button);

        void SetCursorVisible(bool a_Visible);
        void CaptureCursor();

    private:

        static tabi::unordered_map<EMouse, unsigned int> ms_MouseTable;
        static tabi::unordered_map<EKeyboard, unsigned int> ms_KeyboardTable;
        static tabi::unordered_map<EController, unsigned int> ms_ControllerTable;

        tabi::unordered_map<EInputDevice, unsigned int> m_InputDeviceTable;

        unsigned int m_WindowWidth;
        unsigned int m_WindowHeight;

        // Mouse delta
        float m_MouseDeltaX;
        float m_MouseDeltaY;
        // Raw input device
        RAWINPUTDEVICE m_RawInputDevice;
        tabi::vector<char> m_RawBuffer;

        // Mouse capture
        bool m_CaptureMouse = false;

        // Cursor visibility
        /// True if the cursor should be hidden
        bool m_HideCursor = false;
        /// True if the cursor is currently visible
        bool m_CursorVisible = true;

        // gainput
        ::gainput::InputManager m_GaInputManager;
        ::gainput::InputMap m_InputMap;
    };
}