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

            void SwapBuffer() const;

            const char* GetWindowName() const;
            WindowHandle GetHandle() const;
            IContext* GetContext() const;

        protected:
            IWindow()
                : m_WindowName("IWindow"), m_WindowHandle(nullptr)
            { }

            virtual ~IWindow() = default;

        protected:
            const char* m_WindowName;
            WindowHandle m_WindowHandle;
            tabi::shared_ptr<IContext> m_Context;
        };
    }
}