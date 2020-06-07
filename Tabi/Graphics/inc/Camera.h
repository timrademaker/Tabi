#pragma once

#include <Math/vec3.h>
#include <Math/mat4.h>

enum class ECameraType
{
    Perspective,
    Orthographic,
};

namespace tabi
{
    class Camera
    {
        using RotationType = tabi::vec3;

    public:
        Camera() = default;
        ~Camera() = default;

        void MoveBy(tabi::vec3 a_Translation);
        void MoveTo(tabi::vec3 a_Position);

        void RotateBy(RotationType a_Rotation);
        void RotateTo(RotationType a_Rotation);

        tabi::vec3 GetPosition() const;
        RotationType GetRotation() const;

        tabi::mat4 GetView();
        tabi::mat4 GetProjection();

        void SetNear(const float a_Near);
        void SetFar(const float a_Far);
        void SetFoV(const float a_FoV);

    private:
        void GenerateView();
        void GenerateProjection();

    public:
        ECameraType m_CameraType = ECameraType::Perspective;

    private:
        float m_Near = 0.1f;
        float m_Far = 100.f;
        float m_FoV = 60.0f;
        
        bool m_ViewDirty = true;
        tabi::mat4 m_View;
        bool m_ProjectionDirty = true;
        tabi::mat4 m_Projection;

        tabi::vec3 m_Position;
        RotationType m_Rotation;
    };

}