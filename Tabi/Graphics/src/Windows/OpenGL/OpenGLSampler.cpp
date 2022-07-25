#include "Windows/OpenGL/OpenGLSampler.h"
#include "Windows/OpenGL/OpenGLHelpers.h"

#include <Logging.h>

#include <glad/glad.h>

tabi::Sampler::~Sampler()
{
    Unload();
}

bool tabi::Sampler::UseSampler()
{
    glBindSampler(0, m_SamplerID);

    return !tabi::graphics::helpers::CheckForErrors();
}

bool tabi::Sampler::Initialize(tabi::EWrap a_WrapModeS, tabi::EWrap a_WrapModeT, tabi::EMinFilter a_MinFilter, tabi::EMagFilter a_MagFilter)
{
    glGenSamplers(1, &m_SamplerID);
    glBindSampler(0, m_SamplerID);

    // Wrapping
    glSamplerParameteri(m_SamplerID, GL_TEXTURE_WRAP_S, ConvertWrapMode(a_WrapModeS));
    glSamplerParameteri(m_SamplerID, GL_TEXTURE_WRAP_T, ConvertWrapMode(a_WrapModeT));

    // Filtering
    glSamplerParameteri(m_SamplerID, GL_TEXTURE_MIN_FILTER, ConvertMinFilter(a_MinFilter));
    glSamplerParameteri(m_SamplerID, GL_TEXTURE_MAG_FILTER, ConvertMagFilter(a_MagFilter));

    return !tabi::graphics::helpers::CheckForErrors();
}

void tabi::Sampler::Unload()
{
    if (m_SamplerID != 0)
    {
        glDeleteSamplers(1, &m_SamplerID);
        m_SamplerID = 0;
    }
}

unsigned int tabi::Sampler::ConvertWrapMode(tabi::EWrap a_WrapMode)
{
    switch (a_WrapMode)
    {
    case EWrap::ClampToEdge:
    {
        return GL_CLAMP_TO_EDGE;
        break;
    }
    case EWrap::MirroredRepeat:
    {
        return GL_MIRRORED_REPEAT;
        break;
    }
    case EWrap::Repeat:
    {
        return GL_REPEAT;
        break;
    }
    default:
    {
        TABI_WARN("Unable to convert wrap mode %d", static_cast<unsigned int>(a_WrapMode));
        return 0;
        break;
    }
    }
}

unsigned int tabi::Sampler::ConvertMinFilter(tabi::EMinFilter a_MinFilter)
{
    switch (a_MinFilter)
    {
    case tabi::EMinFilter::Nearest:
    {
        return GL_NEAREST;
        break;
    }
    case tabi::EMinFilter::Linear:
    {
        return GL_LINEAR;
        break;
    }
    case tabi::EMinFilter::NearestMipmapNearest:
    {
        return GL_NEAREST_MIPMAP_NEAREST;
        break;
    }
    case tabi::EMinFilter::LinearMipmapNearest:
    {
        return GL_LINEAR_MIPMAP_NEAREST;
        break;
    }
    case tabi::EMinFilter::NearestMipmapLinear:
    {
        return GL_NEAREST_MIPMAP_LINEAR;
        break;
    }
    case tabi::EMinFilter::LinearMipmapLinear:
    {
        return GL_LINEAR_MIPMAP_LINEAR;
        break;
    }
    default:
    {
        TABI_WARN("Unable to convert min filter %d", static_cast<unsigned int>(a_MinFilter));
        return 0;
        break;
    }
    }
}

unsigned int tabi::Sampler::ConvertMagFilter(EMagFilter a_MagFilter)
{
    switch (a_MagFilter)
    {
    case tabi::EMagFilter::Nearest:
    {
        return GL_NEAREST;
        break;
    }
    case tabi::EMagFilter::Linear:
    {
        return GL_LINEAR;
        break;
    }
    default:
    {
        TABI_WARN("Unable to convert mag filter %d", static_cast<unsigned int>(a_MagFilter));
        return 0;
        break;
    }
    }
}
