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

        public:
            virtual void SwapBuffer() const override;
            virtual void Resize(unsigned int a_Width, unsigned int a_Height) override;

        private:
            unsigned int m_Witdh;
            unsigned int m_Height;

            HDC m_DeviceContext;
        };
    }
}