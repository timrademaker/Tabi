#include "ISampler.h"

#if defined(OPENGL)
#include "Windows/OpenGL/OpenGLSampler.h"
#endif

#include <TabiTypes.h>

using namespace tabi;

tabi::ISampler* tabi::ISampler::CreateSampler(tabi::EWrap a_WrapModeS, tabi::EWrap a_WrapModeT, tabi::EMinFilter a_MinFilter, tabi::EMagFilter a_MagFilter)
{
    ISampler* sampler = new tabi::Sampler();
    sampler->Initialize(a_WrapModeS, a_WrapModeT, a_MinFilter, a_MagFilter);
   
    return sampler;
}

tabi::shared_ptr<ISampler> ISampler::CreateSharedSampler(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter,
    EMagFilter a_MagFilter)
{
    ISampler* s = CreateSampler(a_WrapModeS, a_WrapModeT, a_MinFilter, a_MagFilter);
    return ToShared(s);
}

shared_ptr<ISampler> ISampler::ToShared(ISampler*& a_Rhs)
{
    auto shared = tabi::shared_ptr<Sampler>(static_cast<Sampler*>(a_Rhs));
    a_Rhs = nullptr;
    return std::move(shared);
}
