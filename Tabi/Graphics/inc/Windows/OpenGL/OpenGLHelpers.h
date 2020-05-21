#pragma once

#include <glad/glad.h>

namespace tabi
{
    namespace graphics
    {
        namespace helpers
        {
            // Check if shader compilation resulted in an error
            bool CheckShaderLoadError(unsigned int a_Shader);

            // Check if shader program compilation resulted in an error
            bool CheckShaderProgramError(unsigned int a_Program);

#if defined(GL_DEBUG_OUTPUT)
            void GLAPIENTRY MessageCallback(GLenum a_Source, GLenum a_Type, GLuint a_Id, GLenum a_Severity, GLsizei a_Length, const GLchar* a_Message, const void* a_UserParam);
#endif
        }
    }
}