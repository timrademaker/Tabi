#include "Camera.h"

#include "IRenderer.h"

#include <Logging.h>
#include <Math/TabiMath.h>


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

void tabi::Camera::RotateBy(tabi::vec3 a_Rotation)
{
    m_Rotation += a_Rotation;
    m_ViewDirty = true;

    m_Transform.RotateX(a_Rotation.x);
    m_Transform.RotateY(a_Rotation.y);
    m_Transform.RotateZ(a_Rotation.z);
}

void tabi::Camera::RotateTo(tabi::vec3 a_Rotation)
{
    m_Rotation = a_Rotation;
    m_ViewDirty = true;

    m_Transform.SetRotation(a_Rotation);
}

tabi::vec3 tabi::Camera::GetPosition() const
{
    return m_Transform.GetPosition();
}

tabi::vec3 tabi::Camera::GetEulerRotation() const
{
    return vec3(RadToDeg(m_Rotation.x), RadToDeg(m_Rotation.y), RadToDeg(m_Rotation.z));
}

tabi::vec3 tabi::Camera::GetRotation() const
{
    //return m_Transform.GetRotation();
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

void tabi::Camera::SetFoV(const float a_FoV)
{
    m_FoV = a_FoV;
    m_ProjectionDirty = true;
}

tabi::vec3 tabi::Camera::GetForward() const
{
    return -vec3(m_Transform[2], m_Transform[6], m_Transform[10]);
}

tabi::vec3 tabi::Camera::GetRight() const
{
    return vec3(m_Transform[0], m_Transform[4], m_Transform[8]);
}

tabi::vec3 tabi::Camera::GetUp() const
{
    return vec3(m_Transform[1], m_Transform[5], m_Transform[9]);
}

void tabi::Camera::LookAt(const vec3& a_Target)
{
    const vec3 forward = vec3::Normalize(GetPosition() - a_Target);
    const vec3 right = vec3::Normalize(vec3::Cross(forward, vec3(0, 1, 0)));
    const vec3 up = vec3::Normalize(vec3::Cross(right, forward));
    m_Transform[0] = right.x;
    m_Transform[1] = up.x;
    m_Transform[2] = forward.x;
    m_Transform[4] = right.y;
    m_Transform[5] = up.y;
    m_Transform[6] = forward.y;
    m_Transform[8] = right.z;
    m_Transform[9] = up.z;
    m_Transform[10] = forward.z;
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