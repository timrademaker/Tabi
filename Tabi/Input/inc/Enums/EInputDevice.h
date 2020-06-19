#pragma once

namespace tabi
{
    enum class EInputDevice
    {
        Mouse           = 0 << 0,
        Keyboard        = 1 << 4,
        Controller      = Keyboard << 8
    };
}