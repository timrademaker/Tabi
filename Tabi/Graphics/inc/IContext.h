#pragma once

#include <TabiTypes.h>

namespace tabi
{
    namespace graphics
    {
        class IContext
        {
        public:
            virtual void SwapBuffer() const = 0;
            virtual void Resize(unsigned int a_Width, unsigned int a_Height) = 0;

        public:
            IContext() = default;
            virtual ~IContext() = default;
        };

    }
}
