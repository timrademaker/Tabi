#pragma once

#include "IWindow.h"

namespace tabi
{
    namespace graphics
    {
        class Window : public IWindow
        {
        public:
            Window() = default;
            ~Window() = default;

            static Window* Initialize(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height);

            void Test();
            void DrawShit();
        private:
            
        };

        LRESULT CALLBACK ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    }
}
