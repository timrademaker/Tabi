#pragma once

#include "Enums/TextureEnums.h"

#include <TabiMacros.h>
#include <TabiContainers.h>

namespace tabi
{
	struct RenderTextureView
	{
		class Texture* m_Texture = nullptr;

		// The index of the mimpap level to use
		uint8_t m_MipLevel = 0;
		// If the render texture is an array-like texture (e.g. 2DArray, 3D, cube map array), this specifies the layer of the texture to attach
		uint8_t m_TextureLayer = 0;

		// The cube map face if the texture is a cube map
		ECubemapFace m_CubeFace = ECubemapFace::XPositive;	// TODO: Unsure if D3D12 supports this - RTV has no cube map dimension

		// TODO: D3D12 has plane slice here as well
	};

	struct DepthStencilView
	{
		class Texture* m_Texture = nullptr;

		// The index of the mimpap level to use
		uint8_t m_MipLevel = 0;
		// If the render texture is an array-like texture (e.g. 2DArray, cube map array), this specifies the layer of the texture to attach
		uint8_t m_TextureLayer = 0;

		// The cube map face if the texture is a cube map
		ECubemapFace m_CubeFace = ECubemapFace::XPositive;	// TODO: Unsure if D3D12 supports this - DSV has no cube map dimension
	};

	struct RenderTargetDescription
	{
		static constexpr uint32_t MaxRenderTextures = 8;

		tabi::array<RenderTextureView, MaxRenderTextures> m_RenderTextures;
		DepthStencilView m_DepthStencil;
	};

	class RenderTarget
	{
	public:
		TABI_NO_COPY(RenderTarget);
		TABI_NO_MOVE(RenderTarget);

		inline const RenderTargetDescription& GetRenderTargetDescription() const
		{
			return m_RenderTargetDescription;
		}

	protected:
		RenderTarget(RenderTargetDescription a_RenderTargetDescription)
			: m_RenderTargetDescription(a_RenderTargetDescription)
		{}
		~RenderTarget() = default;

	private:
		RenderTargetDescription m_RenderTargetDescription;
	};
}
