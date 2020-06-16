#pragma once

#include "ISampler.h"

namespace tabi
{
    class Sampler : public ISampler
    {
    public:
        Sampler() = default;
        ~Sampler();

        virtual bool UseSampler() override final;

    protected:
        virtual bool Initialize(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter) override;
    
    private:
        void Unload();

        // Convert EWrap to OpenGL's wrap mode
        static unsigned int ConvertWrapMode(EWrap a_WrapMode);
        // Convert EMinFilter to OpenGL's filter mode
        static unsigned int ConvertMinFilter(EMinFilter a_MinFilter);
        // Convert EMagFilter to OpenGL's filter mode
        static unsigned int ConvertMagFilter(EMagFilter a_MagFilter);

    private:
        unsigned int m_SamplerID = 0;
    };
}