#pragma once

#include <TabiMacros.h>

namespace tabi
{
	struct RenderTargetDescription
	{
		// The texture to render to
		class Texture* m_RenderTexture = nullptr;
		// The depth-stencil buffer to use
		class Texture* m_DepthStencilBuffer = nullptr;

		// The index of the mimpap level to use
		uint8_t m_MipLevel = 0;
		// If the render texture is an array-like texture (e.g. 2DArray, 3D, cubemap), this specifies the layer of the texture to attach
		uint8_t m_TextureLayer = 0;
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
