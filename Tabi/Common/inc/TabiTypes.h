#pragma once

#include <TabiContainers.h>
#include <TabiPointers.h>

#include <TabiPlatform.h>

namespace tabi
{
    namespace files
    {
        using FH = int32_t;
        using FSize = int64_t;
    }

    namespace resources
    {
        using ResouceID = unsigned long long int;
    }

    namespace graphics
    {
#if defined(_WINDOWS)
        using WindowHandle = HWND;
#endif
        using ShaderHandle = unsigned int;
    }
}