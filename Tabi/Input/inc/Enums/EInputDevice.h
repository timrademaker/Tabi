#pragma once

namespace tabi
{
    enum class EInputDevice
    {
        Mouse           = 1 << 4,
        Keyboard        = Mouse << 4,
        Controller      = Keyboard << 16
    };
}