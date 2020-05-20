#pragma once

#include <TabiTypes.h>

#include "IContext.h"

namespace tabi
{
    namespace graphics
    {
        class IWindow
        {
        public:
            static tabi::shared_ptr<IWindow> OpenWindow(const char* a_WindowName, unsigned int a_Width, unsigned int a_Height);

            virtual void SwapBuffer() const = 0;

            const char* GetWindowName() { return m_WindowName; }
            WindowHandle GetHandle() const { return m_WindowHandle; }
            const IContext* GetContext() const { return m_Context; }

        protected:
            IWindow()
                : m_WindowName("IWindow"), m_WindowHandle(nullptr)
            { }

            virtual ~IWindow() = default;

        protected:
            const char* m_WindowName;
            WindowHandle m_WindowHandle;
            IContext* m_Context;
        };
    }
}