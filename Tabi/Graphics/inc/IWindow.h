#pragma once

#include <TabiTypes.h>

namespace tabi
{
    namespace graphics
    {
        class IWindow
        {
        public:
            static tabi::shared_ptr<IWindow> OpenWindow(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height);


            const char* GetWindowName() { return m_WindowName; }
            unsigned int GetHeight() const { return m_Height; }
            unsigned int GetWidth() const { return m_Width; }
            WindowHandle GetHandle() const { return m_WindowHandle; }

        protected:
            IWindow()
                : m_Width(0), m_Height(0), m_WindowHandle(nullptr)
            { }

            virtual ~IWindow() = default;

        protected:
            const char* m_WindowName;
            unsigned int m_Width;
            unsigned int m_Height;
            WindowHandle m_WindowHandle;
        };
    }
}