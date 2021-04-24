#pragma once

#include <Math/vec3.h>
#include <Math/mat4.h>

namespace tabi
{
    struct Transform
    {
        tabi::vec3 m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
        tabi::vec3 m_Scale = tabi::vec3{ 1.0f, 1.0f, 1.0f };
        tabi::vec3 m_EulerRotation = tabi::vec3{ 0.0f, 0.0f, 0.0f };

        TABI_INLINE tabi::mat4 GetTransformationMatrix() const
        {
            return tabi::mat4::CreateTransformationMatrix
            (
                tabi::mat4::Translate(tabi::mat4::Identity(), m_Position),
                tabi::mat4::Scale(tabi::mat4::Identity(), m_Scale),
                tabi::mat4::SetRotation(tabi::mat4::Identity(), m_EulerRotation)
            );
        }
    };
}
