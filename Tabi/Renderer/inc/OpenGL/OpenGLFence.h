#pragma once

#include "IFence.h"

#include <glad/glad.h>

#include <atomic>

namespace tabi
{
	class OpenGLFence : public IFence
	{
	public:
		inline void SetCompletionValue(int64_t a_Value) { m_CompletionValue = a_Value; }
		inline void Complete() { m_CurrentValue = m_CompletionValue; }

		virtual uint64_t GetFenceValue() override;

		void Destroy()
		{
			glDeleteSync(m_FenceSync);
			m_FenceSync = nullptr;
		}

	public:
		::GLsync m_FenceSync;

	private:
		uint64_t m_CompletionValue = 0;
		std::atomic<uint64_t> m_CurrentValue{ 0 };
	};
}
