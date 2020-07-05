#include "Windows/OpenGL/OpenGLHelpers.h"

#include <TabiMacros.h>
#include <Logging.h>
#include <ConsoleSink.h>

#include <glad/glad.h>

#define INFO_BUFFER_SIZE 512

tabi::logger::LoggerPtr tabi::graphics::helpers::m_GraphicsLogger = tabi::logger::CreateTabiLogger<tabi::logger::ConsoleSink>("TabiGraphics");

bool tabi::graphics::helpers::CheckShaderLoadSuccess(unsigned int a_Shader)
{
    int success;
    glGetShaderiv(a_Shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char info[INFO_BUFFER_SIZE];
        glGetShaderInfoLog(a_Shader, INFO_BUFFER_SIZE, nullptr, &info[0]);
        m_GraphicsLogger->Log(tabi::logger::ELogLevel::Error, "Error while loading shader: " + tabi::string(info));
    }

    return success;
}

bool tabi::graphics::helpers::CheckShaderProgramSuccess(unsigned int a_Program)
{
    int success;
    glGetProgramiv(a_Program, GL_LINK_STATUS, &success);

    if (!success)
    {
        char info[INFO_BUFFER_SIZE];
        glGetProgramInfoLog(a_Program, INFO_BUFFER_SIZE, nullptr, &info[0]);
        m_GraphicsLogger->Log(tabi::logger::ELogLevel::Error, "Error while loading shader: " + tabi::string(info));
    }

    return success;
}
bool tabi::graphics::helpers::CheckForErrors()
{
    bool anyError = false;
    GLenum err = glGetError();
    while (err != GL_NO_ERROR)
    {
        anyError = true;

        const auto errorString = ErrorToString(err);

        m_GraphicsLogger->Log(logger::ELogLevel::Error, "Error " + tabi::to_string(err) + ": " + errorString);

        err = glGetError();
    }

    return anyError;
}

tabi::string tabi::graphics::helpers::ErrorToString(GLenum a_Error)
{
    tabi::string errorString;

    switch (a_Error)
    {
    case GL_INVALID_ENUM:
    {
        errorString = "GL_INVALID_ENUM";
        break;
    }
    case GL_INVALID_VALUE:
    {
        errorString = "GL_INVALID_VALUE";
        break;
    }
    case GL_INVALID_OPERATION:
    {
        errorString = "GL_INVALID_OPERATION";
        break;
    }
    case GL_OUT_OF_MEMORY:
    {
        errorString = "GL_OUT_OF_MEMORY";
        break;
    }
    case GL_INVALID_FRAMEBUFFER_OPERATION:
    {
        errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
    }
    default:
    {
        errorString = "";
        logger::TabiLog(logger::ELogLevel::Debug, "No string conversion found for enum " + std::to_string(a_Error));
        break;
    }
    }
    
    return errorString;
}

bool tabi::graphics::helpers::IsOpenGLVersionSupported(float a_MinimumRequiredVersion)
{
    std::string version = (char*)(glGetString(GL_VERSION));

    std::string versionNumber = version.substr(0, version.find(" "));

    double value = std::atof(versionNumber.c_str());
    float number = (float)(value * 100 + .5) / 100;

    if(number < a_MinimumRequiredVersion)
    {
        m_GraphicsLogger->Log(logger::ELogLevel::Critical, "The supported OpenGL version ("
            + versionNumber
            + ") is lower than the minimum version required by this program ("
            + tabi::to_string(a_MinimumRequiredVersion).substr(0, 3)
            +")"
        );
        return false;
    }

    return true;
}

#if defined(_DEBUG)
#if defined(GL_DEBUG_OUTPUT)
// OpenGL 4.3 or higher

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
    m_GraphicsLogger->Log(severity, "Type: " + std::to_string(a_Type) + "\nMessage: " + a_Message);
}


void tabi::graphics::helpers::EnableOpenGLDebugOutput()
{
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
}
#endif
#endif