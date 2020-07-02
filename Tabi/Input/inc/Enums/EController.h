#pragma once

#include "EInputDevice.h"

namespace tabi
{
    enum class EController
    {
        // D-Pad
        DPadLeft = 1 | static_cast<unsigned int>(EInputDevice::Controller),
        DPadRight,
        DPadUp,
        DPadDown,
        // Face buttons
        FaceLeft,
        ButtonSquare = FaceLeft,
        ButtonX = FaceLeft,
        FaceRight,
        ButtonCircle = FaceRight,
        ButtonB = FaceRight,
        FaceUp,
        ButtonTriangle = FaceUp,
        ButtonY = FaceUp,
        FaceDown,
        ButtonCross = FaceDown,
        ButtonA = FaceDown,
        // Special
        SpecialLeft,
        Select = SpecialLeft,
        SpecialRight,
        Start = SpecialRight,
        Home,
        // Shoulder buttons/bumpers
        L1,
        LeftShoulder = L1,
        L2,
        LeftBumper = L2,
        L3,
        LeftThumbstickButton = L3,
        R1,
        RightShoulder = R1,
        R2,
        RightBumper = R2,
        R3,
        RightThumbStickButton = R3,
        // Sticks
        LeftStickX,
        LeftStickY,
        RightStickX,
        RightStickY,
        // Gyroscope
        GyroscopeX,
        GyroscopeY,
        GyroscopeZ,
        // Magnetic field (whatever that may be, probably mobile sensors)
        MagneticFieldX,
        MagneticFieldY,
        MagneticFieldZ
    };
}