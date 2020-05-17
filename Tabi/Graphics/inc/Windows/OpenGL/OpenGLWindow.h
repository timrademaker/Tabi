#pragma once

#include "IWindow.h"

#include "OpenGLContext.h"

namespace tabi
{
    namespace graphics
    {
        class Window : public IWindow
        {
        public:
            Window(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height);
            virtual ~Window();

            virtual void SwapBuffer() const override { m_Context->SwapBuffer(); };

            void Test();
            void DrawShit();
        protected:

        private:
            Context* m_Context;
        };

        LRESULT CALLBACK ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    }
}
