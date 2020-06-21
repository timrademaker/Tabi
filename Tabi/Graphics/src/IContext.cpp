#include "IContext.h"

void tabi::graphics::IContext::GetContextDimensions(unsigned int& a_Width, unsigned int& a_Height) const
{
    a_Width = m_Width;
    a_Height = m_Height;
}