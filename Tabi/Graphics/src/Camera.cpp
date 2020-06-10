#include "Camera.h"

#include "IRenderer.h"

#include <Logging.h>
#include <Math/TabiMath.h>


void tabi::Camera::MoveBy(tabi::vec3 a_Translation)
{
    m_Position -= a_Translation;
    m_ViewDirty = true;
}

void tabi::Camera::MoveTo(tabi::vec3 a_Position)
{
    m_Position = -a_Position;
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

void tabi::Camera::GenerateView()
{
    if (m_ViewDirty)
    {
        tabi::mat4 translation = tabi::mat4::Identity();
        translation.Translate(m_Position);

        tabi::mat4 rotation = tabi::mat4::Identity();
        rotation.RotateX(m_Rotation.x);
        rotation.RotateY(m_Rotation.y);
        rotation.RotateZ(m_Rotation.z);

        m_View = mat4::CreateTransformationMatrix(translation, mat4::Identity(), rotation);

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