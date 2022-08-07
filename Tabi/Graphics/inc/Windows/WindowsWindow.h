#pragma once

#include "IWindow.h"

namespace tabi
{
    namespace graphics
    {
        class Window final : public IWindow
        {
        public:
            Window() = default;
            virtual ~Window() = default;

            static const char* GetWindowClassName();

        private:
            virtual bool InitializeWindow(const char* a_WindowName, uint32_t a_Width, uint32_t a_Height) override;

        private:
            static const char* ms_WindowClassName;
        };

        LRESULT CALLBACK ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    }
}
