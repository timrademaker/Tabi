#pragma once

#include "Enums/ComparisonFunction.h"
#include "Enums/SamplerEnums.h"

#include <TabiMacros.h>

namespace tabi
{
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
        float m_MinLOD = -1000.0f;
        // Highest LOD to use. Must be higher than m_MinLOD.
        float m_MaxLOD = 1000.0f;
        // Offset from the calculated mipmap level. If the calculated level is 3 and the bias is 2, the texture will be sampled at level 5
        float m_MipLODBias = 0.0f;
        // The RGBA color to use when m_WrapMode is set to Border. Values should be in range (0.0, 1.0) 
        float m_BorderColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    };

	class Sampler
	{
    public:
        TABI_NO_COPY(Sampler);
        TABI_NO_MOVE(Sampler);

        inline const SamplerDescription& GetSamplerDescription() const
        {
            return m_SamplerDescription;
        }

    protected:
        Sampler(const SamplerDescription& a_SamplerDescription)
            : m_SamplerDescription(a_SamplerDescription)
        {}
        ~Sampler() = default;

	private:
        SamplerDescription m_SamplerDescription;
	};
}