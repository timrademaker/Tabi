#pragma once

#include "IContext.h"



namespace tabi
{
    namespace graphics
    {
        class Context : public IContext
        {
        public:
            Context(HWND a_Hwnd) { m_DeviceContext = GetDC(a_Hwnd); }
            virtual ~Context() = default;

        public:
            virtual void SwapBuffer() const override;
            virtual void Resize() override {}

        private:
            HDC m_DeviceContext;
        };
    }
}