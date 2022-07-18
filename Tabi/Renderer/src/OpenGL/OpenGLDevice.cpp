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
		auto* fence = static_cast<OpenGLFence*>(a_Fence);
		// TODO: Insert into pending commands:
		/*
		fence->m_FenceSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
		*/
	}

	void OpenGLDevice::EndFrame()
	{
		// TODO: Insert into pending commands:
		/*
		while(!m_PendingFences.empty())
		{
			auto* fence = m_PendingFences.front();
			auto result = glClientWaitSync(fence->m_FenceSync, 0, 0);
			if(result == GL_ALREADY_SIGNALED || result == GL_CONDITION_SATISFIED)
			{
				fence->Complete();
				m_PendingFences.pop();
			}
			else
			{
				// Other fences won't have been completed either, as they were inserted later
				break;
			}
		}		
		*/
	}
}
