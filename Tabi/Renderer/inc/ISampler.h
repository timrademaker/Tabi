#pragma once

#include "Enums/ComparisonFunction.h"

namespace tabi
{
    enum class EFilterMode : uint8_t
    {
        Nearest,                // Selects the nearest texel
        Linear                  // Interpolates between two texels
    };

    enum class EMipMapMode : uint8_t
    {
        Nearest,                // Selects the nearest mipmap layer
        Linear                  // Interpolate between two mipmap layers
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

    struct SamplerDescription
    {
        // The minification filter used when sampling a texture
        EFilterMode m_MinFilter = EFilterMode::Nearest;
        // The magnification filter used when sampling a texture
        EFilterMode m_MagFilter = EFilterMode::Nearest;
        // The way in which to select the mipmap to use
        EMipMapMode m_MipMapMode = EMipMapMode::Nearest;
        // The technique used to resolve texture coordinates when reading outside texture boundaries
        EWrapMode m_WrapMode = EWrapMode::Wrap;
        // The comparison function to use when comparing sampled data against existing sampled data
        EComparisonFunction m_ComparisonFunc = EComparisonFunction::Never;
        // Lowest LOD to use, where 0 is the most detailed mipmap level and anything higher is less detailed
        float m_MinLOD = 0.0f;
        // Highest LOD to use. Must be higher than m_MinLOD.
        float m_MaxLOD = 0.0f;
        // Offset from the calculated mipmap level. If the calculated level is 3 and the bias is 2, the texture will be sampled at level 5
        float m_MipLODBias = 0.0f;
        // The RGBA color to use when m_WrapMode is set to Border. Values should be in range (0.0, 1.0) 
        float[4] m_BorderColor{ 0.0f, 0.0f, 0.0f, 0.0f };
    };

	class ISampler
	{

	};
}