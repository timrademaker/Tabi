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

        /**
         * @brief Move the camera by a given translation
         * @params a_Translation The translation to move the camera by
         */
        void MoveBy(tabi::vec3 a_Translation);
        /**
         * @brief Move the camera to a given position
         * @params a_Position The position to move the camera to
         */
        void MoveTo(tabi::vec3 a_Position);

        /**
         * @brief Rotate the camera by a given rotation
         * @params a_Rotation The rotation to rotate the camera with (in radians)
         */
        void RotateBy(tabi::vec3 a_Rotation);
        /**
         * @brief Set the camera's rotation to a given rotation
         * @params a_Rotation The rotation to set the camera's rotation to (in radians)
         */
        void RotateTo(tabi::vec3 a_Rotation);

        /**
         * @brief Get the current position of the camera
         * @returns The position of the camera
         */
        tabi::vec3 GetPosition() const;
        /**
         * @brief Get the current rotation of the camera in degrees
         * @returns The rotation of the camera
         */
        tabi::vec3 GetEulerRotation() const;
        /**
         * @brief Get the current rotation of the camera in radians
         * @returns The rotation of the camera
         */
        tabi::vec3 GetRotation() const;

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
         * @params a_Near The distance to the near clipping plane
         */
        void SetNear(const float a_Near);
        /**
         * @brief Set the far clipping plane of the camera
         * @params a_Far The distance to the far clipping plane
         */
        void SetFar(const float a_Far);
        /**
         * @brief Set the field of view of the camera
         * @params a_FoV The new FoV of the camera (in radians)
         */
        void SetFoV(const float a_FoV);

        tabi::vec3 GetForward() const;
        tabi::vec3 GetRight() const;
        tabi::vec3 GetUp() const;

    private:
        void GenerateView();
        void GenerateProjection();

    public:
        ECameraType m_CameraType = ECameraType::Perspective;

    private:
        float m_Near = 0.1f;
        float m_Far = 100.f;
        // The FoV of the camera in radians
        float m_FoV = 1.04f;
        
        bool m_ViewDirty = true;
        tabi::mat4 m_View;
        bool m_ProjectionDirty = true;
        tabi::mat4 m_Projection;

        RotationType m_Rotation;

        tabi::mat4 m_Transform;
    };

}