#pragma once

#include "EInputDevice.h"

namespace tabi
{
    enum class EMouse
    {
        Left = 1 | static_cast<unsigned>(EInputDevice::Mouse),
        Right,
        Middle = 4 | static_cast<unsigned>(EInputDevice::Mouse),
        Mouse4 = 5 | static_cast<unsigned>(EInputDevice::Mouse),
        Mouse5 = 6 | static_cast<unsigned>(EInputDevice::Mouse),
        MouseX,
        MouseY,
        WheelUp,
        WheelDown
    };
}