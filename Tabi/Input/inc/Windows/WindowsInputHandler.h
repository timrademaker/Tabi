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
        virtual ~InputHandler() override = default;

        virtual void Update() override;

        virtual bool IsButtonDown(EKeyboard a_Button, bool* a_DownLastFrame = nullptr) const override;
        virtual bool IsButtonDown(EController a_Button, bool* a_DownLastFrame = nullptr) const override;
        virtual bool IsButtonDown(EMouse a_Button, bool* a_DownLastFrame = nullptr) const override;

        virtual bool AnyButtonDown() const override;

        virtual float GetAxisValue(EController a_Axis, float* a_Delta = nullptr) const override;
        virtual float GetAxisValue(EMouse a_Axis, float* a_Delta = nullptr) const override;

        virtual void SetMouseCursorVisible(bool a_Visible) override;
        virtual void SetMouseCursorCapture(bool a_Capture) override;
        
        virtual void HandleWindowMsg(const void* a_Msg) override;


    private:
        bool IsButtonDownInternal(unsigned int a_Button, bool* a_DownLastFrame = nullptr) const;
        float GetAxisValueInternal(unsigned int a_Axis, float* a_Delta = nullptr) const;

        // Convert buttons to their internal equivalent (gainput)
        static unsigned int ConvertButton(EMouse a_Button);
        static unsigned int ConvertButton(EKeyboard a_Button);
        static unsigned int ConvertButton(EController a_Button);
        
        // Convert device type to its internal equivalent (gainput)
        unsigned int ConvertDeviceType(EInputDevice a_Device);

        bool IsBound(unsigned int a_Button) const;

        void SetCursorVisible(bool a_Visible);
        void CaptureCursor();
        void SetCursorIcon(LPTSTR a_CursorIcon) const;

    private:
        const HWND m_WindowHandle;
        RECT m_WindowRect{ 0 };
        bool m_MouseIsInWindowRect = false;

        static tabi::unordered_map<EMouse, unsigned int> ms_MouseTable;
        static tabi::unordered_map<EKeyboard, unsigned int> ms_KeyboardTable;
        static tabi::unordered_map<EController, unsigned int> ms_ControllerTable;

        tabi::unordered_map<EInputDevice, unsigned int> m_InputDeviceTable;

        unsigned int m_WindowWidth = 0;
        unsigned int m_WindowHeight = 0;

        // Mouse delta in whatever units Windows uses for this (probably pixels)
        int m_MouseDeltaX = 0;
        int m_MouseDeltaY = 0;
        // Raw input device
        RAWINPUTDEVICE m_RawInputDevice;
        tabi::vector<char> m_RawBuffer;

        // Delta of the mouse wheel since the last frame. Positive means up, negative means down
        float m_MouseWheelDeltaY = 0.0f;

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