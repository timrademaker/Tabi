#pragma once
#include "TabiPointers.h"

namespace tabi
{
    // Magnification filter type
    enum class EMagFilter
    {
        // Selects the texel with its center closest to the texture coordinate. Not using mipmaps.
        Nearest,
        // Approximates the color between the nearest texels. Not using mipmaps.
        Linear
    };

    // Minification filter type
    enum class EMinFilter
    {
        // Selects the texel with its center closest to the texture coordinate. Not using mipmaps.
        Nearest,
        // Approximates the color between the nearest texels. Not using mipmaps.
        Linear,
        // Does the same as Nearest, but uses the nearest mipmap.
        NearestMipmapNearest,
        // Does the same as Linear, but uses the nearest mipmap.
        LinearMipmapNearest,
        // Does the same as Nearest, but linearly interpolates between mipmaps.
        NearestMipmapLinear,
        // Does the same as Linear, but linearly interpolates between mipmaps.
        LinearMipmapLinear
    };

    // Wrapping mode
    enum class EWrap
    {
        // Texture coordinates are clamped to [0, 1]
        ClampToEdge,
        // Texture coordinates wrap around like a mirror (-0.2 becomes 0.2, 1.2 becomes 0.8)
        MirroredRepeat,
        // Texture coordinate wraps around the texture (-0.2 becomes 0.8, 1.2 becomes 0.2)
        Repeat
    };

    class ISampler
    {
    public:
        /**
        * @brief Creates a new sampler
        * @param a_WrapModeS The wrap mode for the S texture coordinates
        * @param a_WrapModeT The wrap mode for the T texture coordinates
        * @param a_MinFilter The minification filter used
        * @param a_MagFilter The magnification filter used
        * @returns The created sampler
        */
        static ISampler* CreateSampler(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter);
        static tabi::shared_ptr<ISampler> CreateSharedSampler(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter);

        /**
         * @brief Turns a raw ISampler pointer into a shared pointer
         * @param a_Rhs The pointer to convert to a shared pointer. Do not use afterwards.
         * @returns The created shared pointer
         */
        static tabi::shared_ptr<ISampler> ToShared(ISampler*& a_Rhs);

        /**
        * @brief Use this sampler
        * @returns True if binding the sampler was successful
        */
        virtual bool UseSampler() = 0;

    protected:
        ISampler() = default;
        virtual ~ISampler() = default;

        /**
        * @brief Internal creation of the shader
        * @param a_WrapModeS The wrap mode for the S texture coordinates
        * @param a_WrapModeT The wrap mode for the T texture coordinates
        * @param a_MinFilter The minification filter used
        * @param a_MagFilter The magnification filter used
        * @returns True if the sampler was created successfully
        */
        virtual bool Initialize(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter) = 0;

    };

}
