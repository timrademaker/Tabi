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
            virtual void Resize() = 0;

        public:
            IContext() = default;
            virtual ~IContext() = default;
        };

    }
}
