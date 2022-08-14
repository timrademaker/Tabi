#pragma once

#include "EInputDevice.h"

namespace tabi
{
    enum class EMouse
    {
        Left = 1 | static_cast<unsigned>(EInputDevice::Mouse),
        Right,
        Middle,
        Mouse4,
        Mouse5,
        MouseX,
        MouseY,
        Wheel,
    };
}