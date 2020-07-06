#include "Camera.h"

#include "IRenderer.h"

#include <Logging.h>
#include <Math/TabiMath.h>


void tabi::Camera::MoveBy(tabi::vec3 a_Translation)
{
    m_Position += a_Translation;
    m_ViewDirty = true;
}

void tabi::Camera::MoveTo(tabi::vec3 a_Position)
{
    m_Position = a_Position;
    m_ViewDirty = true;
}

void tabi::Camera::RotateBy(tabi::vec3 a_Rotation)
{
    m_Rotation += a_Rotation;
    m_ViewDirty = true;
}

void tabi::Camera::RotateTo(tabi::vec3 a_Rotation)
{
    m_Rotation = a_Rotation;
    m_ViewDirty = true;
}

tabi::vec3 tabi::Camera::GetPosition() const
{
    return m_Position;
}

tabi::vec3 tabi::Camera::GetEulerRotation() const
{
    return tabi::vec3(RadToDeg(m_Rotation.x), RadToDeg(m_Rotation.y), RadToDeg(m_Rotation.z));
}

tabi::vec3 tabi::Camera::GetRotation() const
{
    return m_Rotation;
}

tabi::mat4 tabi::Camera::GetView()
{
    GenerateView();
    return m_View;
}

tabi::mat4 tabi::Camera::GetProjection()
{
    GenerateProjection();
    return m_Projection;
}

void tabi::Camera::SetNear(const float a_Near)
{
    m_Near = a_Near;
    m_ProjectionDirty = true;
}

void tabi::Camera::SetFar(const float a_Far)
{
    m_Far = a_Far;
    m_ProjectionDirty = true;
}

void tabi::Camera::SetFoV(const float a_FoV)
{
    m_FoV = a_FoV;
    m_ProjectionDirty = true;
}

tabi::vec3 tabi::Camera::GetForward() const
{
    tabi::vec3 dir;
    dir.x = cos(m_Rotation.y) * cos(m_Rotation.x);
    dir.y = sin(m_Rotation.x);
    dir.z = sin(m_Rotation.y) * cos(m_Rotation.x);
    dir.Normalize();
    return dir;
}

tabi::vec3 tabi::Camera::GetRight() const
{
    return tabi::vec3::Normalize(tabi::vec3::Cross(GetForward(), tabi::vec3(0.0f, 1.0f, 0.0f)));
}

tabi::vec3 tabi::Camera::GetUp() const
{
    return tabi::vec3::Normalize(tabi::vec3::Cross(GetRight(), GetForward()));
}

void tabi::Camera::GenerateView()
{
    if (m_ViewDirty)
    {
        m_View = mat4::CreateLookAtMatrix(m_Position, m_Position + GetForward(), tabi::vec3(0, 1, 0));

        m_ViewDirty = false;
    }
}

void tabi::Camera::GenerateProjection()
{
    if (m_ProjectionDirty)
    {
        if (m_CameraType == ECameraType::Perspective)
        {
            unsigned int width;
            unsigned int height;
            graphics::IRenderer::GetInstance().GetWindowDimensions(width, height);
            const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
            m_Projection = mat4::CreatePerspectiveProjectionMatrix(m_FoV, aspectRatio, m_Near, m_Far);
        }
        else if(m_CameraType == ECameraType::Orthographic)
        {
            tabi::logger::TabiLog(tabi::logger::ELogLevel::Error, "Ortographic camera projection not implemented!");
        }

        m_ProjectionDirty = false;
    }

}