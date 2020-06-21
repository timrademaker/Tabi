#pragma once

#include "IContext.h"



namespace tabi
{
    namespace graphics
    {
        class Context : public IContext
        {
        public:
            Context(HWND a_Hwnd, unsigned int a_Width, unsigned int a_Height);
            virtual ~Context() = default;

            virtual void SwapBuffer() const override;
            virtual void Resize(unsigned int a_Width, unsigned int a_Height) override;

        private:
            HDC m_DeviceContext;
        };
    }
}