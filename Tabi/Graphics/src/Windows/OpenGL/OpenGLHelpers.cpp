#include "Windows/OpenGL/OpenGLHelpers.h"

#include <TabiMacros.h>
#include <Logging.h>

#include <glad/glad.h>

#define INFO_BUFFER_SIZE 512

bool tabi::graphics::helpers::CheckMeshLoadError(unsigned int a_Buffer)
{
    TABI_UNUSED(a_Buffer);

    return false;
}

bool tabi::graphics::helpers::CheckShaderLoadError(unsigned int a_Shader)
{
    int success;
    glGetShaderiv(a_Shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char info[INFO_BUFFER_SIZE];
        glGetShaderInfoLog(a_Shader, INFO_BUFFER_SIZE, nullptr, &info[0]);
        tabi::logger::TabiLog(tabi::logger::ELogLevel::Error, "Error while loading shader: " + tabi::string(info));
    }

    return success;
}

bool tabi::graphics::helpers::CheckShaderProgramError(unsigned int a_Program)
{
    int success;
    glGetProgramiv(a_Program, GL_LINK_STATUS, &success);

    if (!success)
    {
        char info[INFO_BUFFER_SIZE];
        glGetProgramInfoLog(a_Program, INFO_BUFFER_SIZE, nullptr, &info[0]);
        tabi::logger::TabiLog(tabi::logger::ELogLevel::Error, "Error while loading shader: " + tabi::string(info));
    }

    return success;
}