#include "Camera.h"

#include <Logging.h>

void tabi::Camera::MoveBy(tabi::vec3 a_Translation)
{
    m_Transform.Translate(a_Translation);
    m_ViewDirty = true;
}

void tabi::Camera::MoveTo(tabi::vec3 a_Position)
{
    m_Transform.SetPosition(a_Position);
    m_ViewDirty = true;
}

tabi::vec3 tabi::Camera::GetPosition() const
{
    return m_Transform.GetPosition();
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

const tabi::mat4& tabi::Camera::GetTransform() const
{
    return m_Transform;
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

void tabi::Camera::SetAspectRatio(float a_AspectRatio)
{
    m_AspectRatio = a_AspectRatio;
    m_ProjectionDirty = true;
}

void tabi::Camera::SetFoV(const float a_FoV)
{
    m_FoV = a_FoV;
    m_ProjectionDirty = true;
}

tabi::vec3 tabi::Camera::GetForward() const
{
    return m_Transform.GetForward();
}

tabi::vec3 tabi::Camera::GetRight() const
{
    return m_Transform.GetRight();
}

tabi::vec3 tabi::Camera::GetUp() const
{
    return m_Transform.GetUp();
}

void tabi::Camera::LookAt(const vec3& a_Target)
{
    m_Transform.LookAt(a_Target);

    m_ViewDirty = true;
}

void tabi::Camera::GenerateView()
{
    if (m_ViewDirty)
    {
        m_View = mat4::CreateLookAtMatrix(GetPosition(), GetPosition() + GetForward(), tabi::vec3(0, 1, 0));

        m_ViewDirty = false;
    }
}

void tabi::Camera::GenerateProjection()
{
    if (m_ProjectionDirty)
    {
        if (m_CameraType == ECameraType::Perspective)
        {
            m_Projection = mat4::CreatePerspectiveProjectionMatrix(m_FoV, m_AspectRatio, m_Near, m_Far);
        }
        else if(m_CameraType == ECameraType::Orthographic)
        {
            tabi::logger::TabiLog(tabi::logger::ELogLevel::Error, "Orthographic camera projection not implemented!");
        }

        m_ProjectionDirty = false;
    }

}