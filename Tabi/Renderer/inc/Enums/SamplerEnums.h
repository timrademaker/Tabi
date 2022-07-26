#pragma once

namespace tabi
{
    enum class EFilterMode : uint8_t
    {
        // Selects the nearest texel
        Nearest,
        // Interpolates between two texels
        Linear
    };

    enum class EMipMapMode : uint8_t
    {
        // Selects the nearest mipmap layer
        Nearest,
        // Interpolate between two mipmap layers
        Linear
    };

    enum class EWrapMode : uint8_t
    {
        // Texture coordinate wraps around the texture (-0.2 becomes 0.8, 1.2 becomes 0.2)
        Wrap,
        // Texture coordinates wrap around like a mirror (-0.2 becomes 0.2, 1.2 becomes 0.8)
        Mirror,
        // Texture coordinates outside of [0.0, 1.0] are clamped to 0.0 or 1.0 respectively
        Clamp,
        // Texture coordinates outside of [0.0, 1.0] are set to the specified border color
        Border
    };
}
