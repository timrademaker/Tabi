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
            /**
            * @brief Check if shader loading resulted in an error
            * @returns True if no errors were found
            */
            static bool CheckShaderLoadSuccess(unsigned int a_Shader);

            /**
            * @brief Check if shader program compilation resulted in an error
            * @returns True if no errors were found
            */
            static bool CheckShaderProgramSuccess(unsigned int a_Program);

            /**
            * @brief Check for any OpenGL errors
            * @returns True if an error is found
            */
            static bool CheckForErrors();

            // Convert an OpenGL error enum to a string
            static tabi::string ErrorToString(GLenum a_Error);

            // Check if the version of OpenGL you are trying to use is supported
            static bool IsOpenGLVersionSupported(float a_MinimumRequiredVersion);

#if defined(_DEBUG)
#if defined(GL_DEBUG_OUTPUT)
            // Enables OpenGL debug output if possible
            static void EnableOpenGLDebugOutput();
#endif
#endif
        };
    }
}