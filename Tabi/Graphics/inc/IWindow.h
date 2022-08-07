#pragma once

#include <TabiTypes.h>

#include <TabiEvent.h>

namespace tabi
{
    struct WindowResizeEventData
    {
        uint32_t m_NewWidth = 0;
        uint32_t m_NewHeight = 0;
    };
    DECLARE_EVENT(WindowResizeEvent, WindowResizeEventData);

    namespace graphics
    {
        class IWindow
        {
        public:
            static void Initialize(const char* a_WindowName, uint32_t a_Width, uint32_t a_Height);
            static IWindow& GetInstance();

            const char* GetWindowName() const;
            WindowHandle GetHandle() const;
            void Resize(uint32_t a_Width, uint32_t a_Height);
            void GetWindowDimensions(uint32_t& a_Width, uint32_t& a_Height) const
            {
                a_Width = m_Width;
                a_Height = m_Height;
            }

            const WindowResizeEvent& OnWindowResize() const { return m_OnWindowResizeEvent; }

        protected:
            IWindow()
                : m_WindowName("IWindow"), m_WindowHandle(nullptr)
            { }

            virtual ~IWindow() = default;

            virtual bool InitializeWindow(const char* a_WindowName, uint32_t a_Width, uint32_t a_Height) = 0;

        protected:
            const char* m_WindowName;
            WindowHandle m_WindowHandle;

        private:
            uint32_t m_Width = 0;
            uint32_t m_Height = 0;

            WindowResizeEvent m_OnWindowResizeEvent;
        };
    }
}