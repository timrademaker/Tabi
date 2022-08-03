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
        Camera(float a_AspectRatio)
	        : m_AspectRatio(a_AspectRatio)
        {}
        ~Camera() = default;

        /**
         * @brief Move the camera by a given translation
         * @param a_Translation The translation to move the camera by
         */
        void MoveBy(tabi::vec3 a_Translation);
        /**
         * @brief Move the camera to a given position
         * @param a_Position The position to move the camera to
         */
        void MoveTo(tabi::vec3 a_Position);

        /**
         * @brief Get the current position of the camera
         * @returns The position of the camera
         */
        tabi::vec3 GetPosition() const;

        /**
         * @brief Get the current view matrix of the camera
         * @returns The view matrix
         */
        tabi::mat4 GetView();
        /**
         * @brief Get the current projection matrix of the camera
         * @returns The projection matrix
         */
        tabi::mat4 GetProjection();

        /**
         * @brief Get the current transformation matrix of the camera
         * @returns The transformation matrix
         */
        const tabi::mat4& GetTransform() const;

        /**
         * @brief Set the near clipping plane of the camera
         * @param a_Near The distance to the near clipping plane
         */
        void SetNear(float a_Near);
        /**
         * @brief Set the far clipping plane of the camera
         * @param a_Far The distance to the far clipping plane
         */
        void SetFar(float a_Far);
        /**
         * @brief Set the camera's aspect ratio
         * @param a_AspectRatio The new aspect ratio
         */
        void SetAspectRatio(float a_AspectRatio);
        /**
         * @brief Set the field of view of the camera
         * @param a_FoV The new FoV of the camera (in radians)
         */
        void SetFoV(float a_FoV);

        tabi::vec3 GetForward() const;
        tabi::vec3 GetRight() const;
        tabi::vec3 GetUp() const;

        void LookAt(const vec3& a_Target);

    private:
        void GenerateView();
        void GenerateProjection();

    public:
        ECameraType m_CameraType = ECameraType::Perspective;

    private:
        float m_Near = 0.1f;
        float m_Far = 100.f;
        float m_AspectRatio = 16.0f / 9.0f;
        // The FoV of the camera in radians
        float m_FoV = 1.04f;
        
        bool m_ViewDirty = true;
        tabi::mat4 m_View;
        bool m_ProjectionDirty = true;
        tabi::mat4 m_Projection;

        tabi::mat4 m_Transform;
    };

}