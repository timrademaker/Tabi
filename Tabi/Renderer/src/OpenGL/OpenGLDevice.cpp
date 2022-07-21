#include "OpenGL/OpenGLDevice.h"

#include "OpenGL/OpenGLFence.h"

namespace tabi
{
	IFence* OpenGLDevice::CreateFence()
	{
		return new OpenGLFence;
	}

	void OpenGLDevice::InsertFence(class IFence* a_Fence, uint64_t a_Value)
	{
		m_CommandQueue.emplace_back([fence = static_cast<OpenGLFence*>(a_Fence)]
			{
				fence->m_FenceSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
			}
		);
	}

	void OpenGLDevice::EndFrame()
	{
		m_CommandQueue.emplace_back([pendingFences = &m_PendingFences]
			{
				while (!pendingFences->empty())
				{
					auto* fence = pendingFences->front();
					const auto result = glClientWaitSync(fence->m_FenceSync, 0, 0);
					if (result == GL_ALREADY_SIGNALED || result == GL_CONDITION_SATISFIED)
					{
						fence->Complete();
						pendingFences->pop();
					}
					else
					{
						// Other fences won't have been completed either, as they were inserted later
						break;
					}
				}
			}
		);
	}
}
