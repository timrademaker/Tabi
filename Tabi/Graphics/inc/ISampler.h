#pragma once
#include "TabiPointers.h"

namespace tabi
{
    // Magnification filter type
    enum class EMagFilter
    {
        Nearest,                // Selects the texel with its center closest to the texture coordinate. Not using mipmaps.
        Linear                  // Approximates the color between the nearest texels. Not using mipmaps.
    };

    // Minification filter type
    enum class EMinFilter
    {
        Nearest,                // Selects the texel with its center closest to the texture coordinate. Not using mipmaps.
        Linear,                 // Approximates the color between the nearest texels. Not using mipmaps.
        NearestMipmapNearest,   // Does the same as Nearest, but uses the nearest mipmap.
        LinearMipmapNearest,    // Does the same as Linear, but uses the nearest mipmap.
        NearestMipmapLinear,    // Does the same as Nearest, but linearly interpolates between mipmaps.
        LinearMipmapLinear      // Does the same as Linear, but linearly interpolates between mipmaps.
    };

    // Wrapping mode
    enum class EWrap
    {
        ClampToEdge,            // Texture coordinates are clamped to [0, 1]
        MirroredRepeat,         // Texture coordinates wrap around like a mirror (-0.2 becomes 0.2, 1.2 becomes 0.8)
        Repeat                  // Texture coordinate wraps around the texture (-0.2 becomes 0.8, 1.2 becomes 0.2)
    };

    class ISampler
    {
    public:
        /**
        * @brief Creates a new sampler
        * @params a_WrapModeS The wrap mode for the S texture coordinates
        * @params a_WrapModeT The wrap mode for the T texture coordinates
        * @params a_MinFilter The minification filter used
        * @params a_MagFilter The magnification filter used
        * @returns The created sampler
        */
        static ISampler* CreateSampler(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter);
        static tabi::shared_ptr<ISampler> CreateSharedSampler(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter);

        /**
         * @brief Turns a raw sampler pointer into a shared pointer
         * @params a_Rhs The pointer to convert to a shared pointer. Do not use afterwards.
         * @returns The shared pointer
         */
        static tabi::shared_ptr<ISampler> ToShared(ISampler*& a_Rhs);

            /**
        * @brief Use the current sampler
        * @returns True if binding the sampler was successful
        */
        virtual bool UseSampler() = 0;

    protected:
        ISampler() = default;
        ~ISampler() = default;

        virtual bool Initialize(EWrap a_WrapModeS, EWrap a_WrapModeT, EMinFilter a_MinFilter, EMagFilter a_MagFilter) = 0;

    };

}
