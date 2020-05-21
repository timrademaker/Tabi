#pragma once

#include "IWindow.h"

namespace tabi
{
    namespace graphics
    {
        class Window : public IWindow
        {
        public:
            Window(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height);
            virtual ~Window();

        };

        LRESULT CALLBACK ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    }
}
