#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

namespace tabi
{
    class vec3;
    class vec4;

    // Row-major 4x4 matrix
    class mat4
    {
    public:
        mat4();
        mat4( float a_00, float a_01, float a_02, float a_03
            , float a_10, float a_11, float a_12, float a_13
            , float a_20, float a_21, float a_22, float a_23
            , float a_30, float a_31, float a_32, float a_33);
        ~mat4() = default;

        mat4 Transpose() const;
        static mat4 Identity();

        // Scaling
        void Scale(const float a_Scale);
        void Scale(const vec3& a_Scale);
        void Scale(const vec4& a_Scale);
        static mat4 Scale(const mat4& a_Matrix, const float a_Scale);
        static mat4 Scale(const mat4& a_Matrix, const vec3& a_Scale);
        static mat4 Scale(const mat4& a_Matrix, const vec4& a_Scale);

        vec3 GetScale() const;
        void SetScale(const vec3& a_Scale);
        static mat4 SetScale(const mat4& a_Matrix, const vec3& a_Scale);

        // Translation
        void Translate(const vec3& a_Translation);
        void Translate(const vec4& a_Translation);
        static mat4 Translate(const mat4& a_Matrix, const vec3& a_Translation);
        static mat4 Translate(const mat4& a_Matrix, const vec4& a_Translation);

        vec3 GetPosition() const;
        void SetPosition(const vec3& a_Position);
        static mat4 SetPosition(const mat4& a_Matrix, const vec3& a_Position);


        // Rotation
        void RotateX(const float a_Radians);
        void RotateY(const float a_Radians);
        void RotateZ(const float a_Radians);
        static mat4 RotateX(const mat4& a_Matrix, const float a_Radians);
        static mat4 RotateY(const mat4& a_Matrix, const float a_Radians);
        static mat4 RotateZ(const mat4& a_Matrix, const float a_Radians);

        /// Set the rotation of the matrix (in radians)
        void SetRotation(const vec3& a_EulerRotation);
        static mat4 SetRotation(const mat4& a_Matrix, const vec3& a_EulerRotation);

        /** 
         * Set the rotation of the matrix in the opposite way of what SetRotation would do
         * @param a_EulerRotation The rotation of which to set the opposite as the rotation of this matrix (will be multiplied by -1 before being used)
         */
        void SetUnRotation(const vec3& a_EulerRotation);
        /**
         * Set the rotation of the matrix in the opposite way of what SetRotation would do
         * @param a_Matrix The matrix to set the rotation in
         * @param a_EulerRotation The rotation of which to set the opposite as the rotation of this matrix (will be multiplied by -1 before being used)
         * @return A matrix with the rotation undone
         */
        static mat4 SetUnRotation(const mat4& a_Matrix, const vec3& a_EulerRotation);

        static mat4 CreateTransformationMatrix(const mat4& a_Translation, const mat4& a_Scale, const mat4& a_Rotation);
        static mat4 CreatePerspectiveProjectionMatrix(const float a_FoV, const float a_AspectRatio, const float a_Near, const float a_Far);
        static mat4 CreateLookAtMatrix(const vec3& a_Eye, const vec3& a_Target, const vec3& a_Up);

        void LookAt(const vec3& a_Target);
        mat4 LookAt(const vec3& a_Target) const;

        // Directions
        tabi::vec3 GetForward() const;
        tabi::vec3 GetRight() const;
        tabi::vec3 GetUp() const;

        // Getters
        float Get(const unsigned int a_Row, const unsigned int a_Column) const;
        float& Get(const unsigned int a_Row, const unsigned int a_Column);

        /**** Operators ****/
        float operator[](const unsigned int a_Index) const;
        float& operator[](const unsigned int a_Index);

        mat4& operator=(const mat4& a_Rhs);

        bool operator==(const mat4& a_Rhs) const;
        bool operator!=(const mat4& a_Rhs) const;

        mat4& operator+=(const mat4& a_Rhs);
        mat4& operator-=(const mat4& a_Rhs);

        mat4& operator*=(const mat4& a_Rhs);
        mat4& operator*=(const float a_Scalar);

        friend mat4 operator*(const mat4& a_Lhs, const float a_Scalar);
        friend vec3 operator*(const mat4& a_Lhs, const vec3& a_Rhs);
        friend vec4 operator*(const mat4& a_Lhs, const vec4& a_Rhs);

        friend mat4 operator*(const mat4& a_Lhs, const mat4& a_Rhs);
        friend mat4 operator+(const mat4& a_Lhs, const mat4& a_Rhs);
        friend mat4 operator-(const mat4& a_Lhs, const mat4& a_Rhs);

    public:
        union
        {
            float m[4][4];
            float v[16];
        };
    };
}


DISABLE_WARNING_POP