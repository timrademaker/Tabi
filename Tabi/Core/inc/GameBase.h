#pragma once

#include <TabiMacros.h>

namespace tabi
{
    class TABI_EXPORT GameBase
    {
    public:
        GameBase(const char* a_Name, const int a_Width, const int a_Height, const bool a_Vsync)
            : m_Width(a_Width), m_Height(a_Height), m_Vsync(a_Vsync), m_Name(a_Name) 
        {}
        virtual ~GameBase() = default;
    
        /**
        * Called after the engine subsystems have been initialized.
        * @return Whether the initialization was successful or not
        */
        virtual bool OnInitialize() { return true; };
        
        /**
        * Called every tick, before engine systems have been updated.
        */
        virtual void OnUpdate(float a_DeltaTime) { TABI_UNUSED(a_DeltaTime); };
        
        /**
        * Called after the engine's rendering has been completed.
        */
        virtual void OnRender() {};
    
        /**
        * Called before the engine shuts down.
        */
        virtual void OnDestroy() {};
    
    
        int GetWindowHeight() const { return m_Height; }
        int GetWindowWidth() const { return m_Width; }
        const char* GetWindowName() const { return m_Name; }
        bool VsyncEnabled() const { return m_Vsync; }
        
    
        GameBase() = delete;
        GameBase(const GameBase&) = delete;
        GameBase& operator=(const GameBase&) = delete;
    
    protected:
        int m_Width;
        int m_Height;
        bool m_Vsync;
        const char* m_Name;
    
    };
}