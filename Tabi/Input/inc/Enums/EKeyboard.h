#pragma once

#include "EInputDevice.h"

namespace tabi
{
    enum class EKeyboard
    {
        // Letters
        A = 1 | static_cast<unsigned>(EInputDevice::Keyboard),
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Minus,
        Equals,
        BracketLeft,
        BracketRight,
        Semicolon,
        Apostrophe,
        Comma,
        Period,
        Slash,
        Backslash,
        AccentGrave,

        // Modifiers
        LeftCtrl,
        Ctrl = LeftCtrl,
        RightCtrl,
        LeftAlt,
        Alt = LeftAlt,
        AltGr,
        RightAlt = AltGr,
        LeftShift,
        Shift = LeftShift,
        RightShift,
        Enter,
        Return = Enter,
        Backspace,
        Escape,
        Space,
        Tab,

        // Arrow keys
        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight,

        // Numbers
        Key0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,

        // Numpad/Keypad
        Keypad0,
        KeypadInsert = Keypad0,
        Keypad1,
        KeypadEnd = Keypad1,
        Keypad2,
        KeypadDown = Keypad2,
        Keypad3,
        KeypadPageDown = Keypad3,
        Keypad4,
        KeypadLeft = Keypad4,
        Keypad5,
        KeypadBegin = Keypad5,
        Keypad6,
        KeypadRight = Keypad6,
        Keypad7,
        KeypadHome = Keypad7,
        Keypad8,
        KeypadUp = Keypad8,
        Keypad9,
        KeypadPageUp = Keypad9,
        KeypadPlus,
        KeypadAdd = KeypadPlus,
        KeypadMinus,
        KeypadSlash,
        KeypadAsterisk,
        KeypadPeriod,
        KeypadEnter,

        // Function keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        Insert,
        Delete,
        Home,
        End,
        PageUp,
        PageDown,
        PrintScreen,
        ScrollLock,
        Pause,
    };
}