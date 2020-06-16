#include "ISampler.h"

#if defined(OPENGL)
#include "Windows/OpenGL/OpenGLSampler.h"
#endif

using namespace tabi;

tabi::ISampler* tabi::ISampler::CreateSampler(tabi::EWrap a_WrapModeS, tabi::EWrap a_WrapModeT, tabi::EMinFilter a_MinFilter, tabi::EMagFilter a_MagFilter)
{
    ISampler* sampler = new tabi::Sampler();
    sampler->Initialize(a_WrapModeS, a_WrapModeT, a_MinFilter, a_MagFilter);
    
    return sampler;
}