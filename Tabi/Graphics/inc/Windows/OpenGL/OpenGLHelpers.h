#pragma once

#include <TabiTypes.h>
#include <Logging.h>

#include <glad/glad.h>

namespace tabi
{
    namespace graphics
    {
        class helpers
        {
        public:
            // Check if shader compilation resulted in an error
            static bool CheckShaderLoadError(unsigned int a_Shader);

            // Check if shader program compilation resulted in an error
            static bool CheckShaderProgramError(unsigned int a_Program);

            // Check for any OpenGL errors
            static void CheckForErrors();

            static tabi::string ErrorToString(GLenum a_Error);

#if defined(_DEBUG)
#if defined(GL_DEBUG_OUTPUT)
            // Enables OpenGL debug output if possible
            static void EnableOpenGLDebugOutput();
#endif
#endif
        private:
            static tabi::logger::LoggerPtr m_GraphicsLogger;
        };
    }
}