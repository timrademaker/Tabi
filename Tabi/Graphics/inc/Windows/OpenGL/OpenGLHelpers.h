#pragma once

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

#if defined(_DEBUG)
#if defined(GL_DEBUG_OUTPUT)
            // Enables OpenGL debug output if possible
            void EnableOpenGLDebugOutput();
#endif
#endif
        }
    }
}