#pragma once

#include "IContext.h"

namespace tabi
{
    namespace graphics
    {
        class Context : public IContext
        {
        public:
            Context() = default;
            virtual ~Context() = default;

        public:
            virtual void SwapBuffer() const override;

        private:
            HDC m_DeviceContext;
        };
    }
}