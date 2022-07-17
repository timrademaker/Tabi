#pragma once

namespace tabi
{
	struct RenderTargetDescription
	{
		// The texture to render to
		class ITexture* m_RenderTexture = nullptr;
		// The depth-stencil buffer to use
		class ITexture* m_DepthStencilBuffer = nullptr;

		// The index of the mimpap level to use
		uint8_t m_MipLevel = 0;
		// If the render texture is an array-like texture (e.g. 2DArray, 3D, cubemap), this specifies the layer of the texture to attach
		uint8_t m_TextureLayer = 0;
	};

	class IRenderTarget
	{
		
	};
}
