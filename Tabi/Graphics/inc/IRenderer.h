#pragma once

#include <TabiTypes.h>

namespace tabi
{
    namespace graphics
    {
        class IRenderer
        {
        public:
            static IRenderer& GetInstance();

        private:
            IRenderer() = default;
            virtual ~IRenderer() = default;

        };
    }
}