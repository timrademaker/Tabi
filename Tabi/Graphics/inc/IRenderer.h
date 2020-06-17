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
            * @brief Load shaders into a shader program
            * @params a_VertexShader The source of the vertex shader
            * @params a_VertexShaderLength The length of the vertex shader. Can be 0 if the shader source is null-terminated.
            * @params a_FragmentShader The source of the fragment shader
            * @params a_FragmentShaderLength The length of the fragment shader. Can be 0 if the shader source is null-terminated.
            * @returns A shader handle
            */
            virtual ShaderHandle CreateShaderProgram(const char* a_VertexShader, const int a_VertexShaderLength, const char* a_FragmentShader, const int a_FragmentShaderLength) const = 0;
            /**
            * @brief Load shaders into a shader program
            * @params a_VertexShaderPath The path to a vertex shader file
            * @params a_FragmentShaderPath The path to a fragment shader file
            * @returns A shader handle
            */
            virtual ShaderHandle CreateShaderProgram(const char* a_VertexShaderPath, const char* a_FragmentShaderPath) const = 0;

            /**
            * @brief Use a loaded shader
            * @params a_ShaderHandle The handle returned by CreateShaderProgram
            */
            virtual void UseShader(const ShaderHandle a_ShaderHandle) = 0;

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

        protected:
            IRenderer() = default;
            virtual ~IRenderer() = default;

        protected:
            unsigned int m_WindowWidth;
            unsigned int m_WindowHeight;
        };
    }
}