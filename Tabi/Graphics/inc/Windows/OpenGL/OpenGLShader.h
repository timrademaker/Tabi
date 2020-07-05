#pragma once

#include "IShader.h"

namespace tabi
{
    class Shader : public IShader
    {
    public:
        virtual bool UseShader() override final;

        virtual bool SetUniformInt(const char* a_UniformName, const int a_Value) override final;
        virtual bool SetUniformVec4f(const char* a_UniformName, const int a_Count, const tabi::vec4* a_Value) override final;
        virtual bool SetUniformMat4f(const char* a_UniformName, const int a_Count, bool a_Transpose, const tabi::mat4* a_Value) override final;

    protected:
        virtual bool Initialize(const char* a_VertexShaderString, const size_t a_VertexShaderLength, const char* a_FragmentShaderString, const size_t a_FragmentShaderLength) override final;

    private:
        int GetUniformLocation(const char* a_UniformName);

    private:
        unsigned int m_ShaderProgram;

        static tabi::map<tabi::string, int> ms_KnownUniformLocations;
    };
}