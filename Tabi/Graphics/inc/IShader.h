#pragma once

#include <TabiPointers.h>
#include <TabiContainers.h>

namespace tabi
{
    class vec4;
    class mat4;

    class IShader
    {
    public:
        /**
        * @brief Creates a new shader
        * @params a_VertexShaderPath The file path of the vertex shader to load
        * @params a_FragmentShaderPath The file path of the fragment shader to load
        * @returns The created shader
        */
        static IShader* CreateShader(const char* a_VertexShaderPath, const char* a_FragmentShaderPath);
        static tabi::shared_ptr<IShader> CreateSharedShader(const char* a_VertexShaderPath, const char* a_FragmentShaderPath);

        /**
        * @brief Creates a new shader
        * @params a_VertexShaderString The vertex shader to load
        * @params a_VertexShaderLength The length of a_VertexShaderString. Can be 0 if the shader source is null-terminated.
        * @params a_FragmentShaderString The fragment shader to load
        * @params a_VertexShaderLength The length of a_FragmentShaderString. Can be 0 if the shader source is null-terminated.
        * @returns The created shader
        */
        static IShader* CreateShader(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength);
        static tabi::shared_ptr<IShader> CreateSharedShader(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength);


        /**
         * @brief Turns a raw IShader pointer into a shared pointer
         * @params a_Rhs The pointer to convert to a shared pointer. Do not use afterwards.
         * @returns The created shared pointer
         */
        static tabi::shared_ptr<IShader> ToShared(IShader*& a_Rhs);

        /**
        * @brief Use this shader
        * @returns True if binding the shader was successful
        */
        virtual bool UseShader() = 0;

        /**
        * @brief Set a uniform integer in the shader
        * @params a_UniformName The name of the uniform used in the shader
        * @params a_Value The value to set the uniform to
        */
        virtual bool SetUniformInt(const char* a_UniformName, const int a_Value) = 0;
        /**
        * @brief Set a uniform vec4 in the shader
        * @params a_UniformName The name of the uniform used in the shader
        * @params a_Count The number of vec4s to set
        * @params a_Value The value to set the uniform to
        */
        virtual bool SetUniformVec4f(const char* a_UniformName, const int a_Count, const tabi::vec4* a_Value) = 0;
        /**
        * @brief Set a uniform vec4 in the shader
        * @params a_UniformName The name of the uniform used in the shader
        * @params a_Count The number of vec4s to set
        * @params a_Transpose True if the matrix should be transposed when loaded into the uniform
        * @params a_Value The value to set the uniform to
        */
        virtual bool SetUniformMat4f(const char* a_UniformName, const int a_Count, bool a_Transpose, const tabi::mat4* a_Value) = 0;
        

    protected:
        IShader() = default;
        ~IShader() = default;

        /**
        * @brief Internal creation of the shader
        * @params a_VertexShaderString The vertex shader to load
        * @params a_VertexShaderLength The length of a_VertexShaderString
        * @params a_FragmentShaderString The fragment shader to load
        * @params a_VertexShaderLength The length of a_FragmentShaderString
        * @returns True if the sampler was created successfully
        */
        virtual bool Initialize(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength) = 0;

    private:
        static bool LoadShaderContent(const char* a_ShaderPath, tabi::vector<char>& a_Content);

    };
}