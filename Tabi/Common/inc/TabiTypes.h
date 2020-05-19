#pragma once

#include <TabiContainers.h>
#include <TabiPointers.h>

#if defined(_WINDOWS)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

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

        using MeshHandle = unsigned int;
        using TextureHandle = unsigned int;
        using ShaderHandle = unsigned int;
    }
}