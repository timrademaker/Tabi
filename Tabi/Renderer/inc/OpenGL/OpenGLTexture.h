#pragma once

#include "Texture.h"

#include <TabiMacros.h>

#include <glad/glad.h>

namespace tabi
{
	class OpenGLTexture : public Texture
	{
	public:
		TABI_NO_COPY(OpenGLTexture);
		TABI_NO_MOVE(OpenGLTexture);

		OpenGLTexture(const TextureDescription& a_TextureDescription)
			: Texture(a_TextureDescription)
		{}

		void Destroy()
		{
			glDeleteTextures(1, &m_TextureID);
			m_TextureID = 0;
		}

		inline GLuint GetID() const { return m_TextureID; }
		inline void SetID(GLuint a_TextureID)
		{
			TABI_ASSERT(m_TextureID == 0, "Texture ID already set!");
			m_TextureID = a_TextureID;
		}

	private:
		GLuint m_TextureID = 0;
	};
}
