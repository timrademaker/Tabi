#pragma once

#include <Enums/ShaderEnums.h>
#include <Enums/Format.h>
#include <Enums/TextureEnums.h>

namespace tabi
{
	class Camera;

	class Shader* LoadShader(const char* a_ShaderPath, tabi::EShaderType a_ShaderType, const char* a_DebugName = nullptr);

	/**
	 * @brief Create a texture with a single mip level
	 * @param a_Format The format of the texture
	 * @param a_Dimension The dimension of the texture
	 * @param a_Width The width of the texture
	 * @param a_Height The height of the texture
	 * @param a_Depth The depth of the texture
	 * @param a_Data The texture data
	 * @param a_DebugName The debug name of the texture
	 */
	class Texture* LoadTexture(EFormat a_Format, ETextureDimension a_Dimension, uint64_t a_Width, uint64_t a_Height, uint16_t a_Depth, const void* a_Data, const char* a_DebugName = nullptr);

	namespace graphics
	{
		void BeginFrame();
		void EndFrame();

		tabi::Camera* GetMainCamera();
		void SetMainCamera(tabi::Camera* a_Camera);
	}
}
