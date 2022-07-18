#include "OpenGL/OpenGLFence.h"

namespace tabi
{
	uint64_t OpenGLFence::GetFenceValue()
	{
		return m_CurrentValue.load();
	}
}