#pragma once

#include <TabiTypes.h>

namespace tabi
{
    namespace graphics
    {
        class IWindow
        {
        public:
            IWindow() = delete;
            IWindow(float a_Width, float a_Height, WindowHandle a_WindowHandle)
                : m_Width(a_Width), m_Height(a_Height), m_WindowHandle(a_WindowHandle)
            {}

            virtual ~IWindow() = default;


            float GetHeight() const { return m_Height; }
            float GetWidth() const { return m_Width; }
            WindowHandle GetHandle() const { return m_WindowHandle; }

        private:
            const float m_Width;
            const float m_Height;
            const WindowHandle m_WindowHandle;
        };
    }
}