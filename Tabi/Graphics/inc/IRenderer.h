#pragma once

#include <TabiTypes.h>

namespace tabi
{
    class Mesh;
    class Texture;

    namespace graphics
    {
        enum class EBufferMode
        {
            Static,     // Modified once, used often
            Dynamic,    // Modified often, used often
            Stream      // Modified once, used a couple of times
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
            * @params a_BufferMode The mode in which to buffer the texture
            * @returns Whether the operation completed successfully
            */
            virtual bool BufferTexture(const Texture& a_Texture, const EBufferMode a_BufferMode = EBufferMode::Static) const = 0;
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

        protected:
            IRenderer() = default;
            virtual ~IRenderer() = default;

        };
    }
}