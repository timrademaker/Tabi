#include "Windows/OpenGL/OpenGLHelpers.h"

#include <TabiMacros.h>
#include <Logging.h>
#include <ConsoleSink.h>

#include <glad/glad.h>

#define INFO_BUFFER_SIZE 512

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

#if defined(GL_DEBUG_OUTPUT)
// OpenGL 4.3 or higher
auto graphicsLogger = tabi::logger::CreateTabiLogger<tabi::logger::ConsoleSink>("TabiGraphics");

void GLAPIENTRY tabi::graphics::helpers::MessageCallback(GLenum a_Source, GLenum a_Type, GLuint a_Id, GLenum a_Severity, GLsizei a_Length, const GLchar* a_Message, const void* a_UserParam)
{
    tabi::logger::ELogLevel severity;
    switch (a_Severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
    {
        severity = tabi::logger::ELogLevel::Error;
        break;
    }
    case GL_DEBUG_SEVERITY_MEDIUM:
    {
        severity = tabi::logger::ELogLevel::Warning;
        break;
    }
    case GL_DEBUG_SEVERITY_LOW:
    {
        severity = tabi::logger::ELogLevel::Info;
        break;
    }
    }
    graphicsLogger->Log(severity, "Type: " + std::to_string(a_Type) + "\nMessage: " + a_Message);
}
#endif

#if defined(_DEBUG)
#if defined(GL_DEBUG_OUTPUT)
void tabi::graphics::helpers::EnableOpenGLDebugOutput()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
}
#endif
#endif