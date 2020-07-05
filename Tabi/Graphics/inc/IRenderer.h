#pragma once

#include <TabiTypes.h>

#include <math/mat4.h>

namespace tabi
{
    class Mesh;
    class Texture;
    class Camera;

    namespace graphics
    {
        class IWindow;

        enum class EBufferMode
        {
            Static,     // Modified once, used often
            Dynamic,    // Modified often, used often
            Stream      // Modified once, used a couple of times
        };

        enum class EDrawMode
        {
            Line,
            Point,
            Fill
        };

        class IRenderer
        {
        public:
            static IRenderer& GetInstance();

            virtual void Initialize(tabi::shared_ptr<IWindow> a_Window);
            bool HasBeenInitialized() const;

            /**
            * @brief Load a mesh into a buffer, and updates the mesh with necessary data
            * @params a_Mesh The mesh to load
            * @params a_CleanUpMeshDataAfterBuffering True if the vertex data should be cleaned up after buffering
            * @params a_BufferMode The mode in which to buffer the mesh
            * @returns Whether the operation completed successfully
            */
            virtual bool BufferMesh(Mesh& a_Mesh, const bool a_CleanUpMeshDataAfterBuffering = true, const EBufferMode a_BufferMode = EBufferMode::Static) const = 0;
            /**
            * @brief Load a texture into a buffer
            * @params a_Mesh The texture to load
            * @params a_CleanUpTextureDataAfterBuffering True if the texture data should be cleaned up after buffering
            * @returns Whether the operation completed successfully
            */
            virtual bool BufferTexture(Texture& a_Texture, const bool a_CleanUpTextureDataAfterBuffering = true) const = 0;

            /**
            * @brief Renders a mesh
            * @params a_Mesh The mesh to render
            */
            virtual void RenderMesh(const Mesh& a_Mesh, const mat4& a_Transform) = 0;


            /**
            * @brief Set a camera as the camera from which the screen is drawn
            * @params a_Camera The camera to use
            */
            virtual void UseCamera(const tabi::shared_ptr<Camera> a_Camera) = 0;

            
            /**
             * @brief Set the draw mode of the renderer
             * @params a_DrawMode The draw mode to use
             */
            virtual void SetDrawMode(EDrawMode a_DrawMode) = 0;

            /**
            * @brief Update the known dimensions of the active window. Doesn't resize the window.
            */
            void UpdateWindowDimensions(unsigned int a_Width, unsigned int a_Height);

            /**
            * @brief Get the active window's dimensions
            * @returns The dimensions of the window
            */
            void GetWindowDimensions(unsigned int& a_Width, unsigned int& a_Height) const;

            const IWindow& GetWindow() const;

        protected:
            IRenderer() = default;
            virtual ~IRenderer() = default;

        protected:
            tabi::shared_ptr<IWindow> m_Window;
            bool m_Initialized = false;
        };
    }
}