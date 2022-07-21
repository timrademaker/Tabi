#include "OpenGL/OpenGLCommandList.h"

#include "OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

#define ENSURE_COMMAND_LIST_IS_RECORDING() TABI_ASSERT(m_IsRecording, "Command list function called while recording is not active!")

void tabi::OpenGLCommandList::BeginRecording()
{
	TABI_ASSERT(m_IsRecording == false, "Command list is already recording!");
	m_IsRecording = true;
}

void tabi::OpenGLCommandList::EndRecording()
{
	TABI_ASSERT(m_IsRecording == true, "Command list is not currently recording!");
	m_IsRecording = false;
}

void tabi::OpenGLCommandList::Reset()
{
	m_PendingCommands.clear();
	m_IsRecording = false;
}

void tabi::OpenGLCommandList::BindVertexBuffers(int32_t a_FirstSlot, Buffer** a_VertexBuffers, size_t a_NumBuffers)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	// Copy the buffers to a vector so we don't have to rely on a_VertexBuffers remaining valid until the command list is executed
	tabi::vector<Buffer*> buffers{ a_NumBuffers };
	for (size_t i = 0; i < a_NumBuffers; ++i)
	{
		buffers.push_back(a_VertexBuffers[i]);
	}

	m_PendingCommands.push_back([a_FirstSlot, a_NumBuffers, buffers = std::move(buffers)]
		{
			tabi::vector<GLuint> vertexBuffers{8};
			tabi::vector<GLsizei> strides{8};

			for (size_t i = 0; i < a_NumBuffers; ++i)
			{
				const OpenGLBuffer* oglBuffer = static_cast<OpenGLBuffer*>(buffers[i]);

				vertexBuffers.push_back(oglBuffer->GetID());
				strides.push_back(buffers[i]->GetBufferDescription().m_Stride);
			}

			glBindVertexBuffers(a_FirstSlot, a_NumBuffers, vertexBuffers.data(), nullptr, strides.data());
		}
	);
}

void tabi::OpenGLCommandList::BindIndexBuffer(Buffer* a_IndexBuffer)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	m_PendingCommands.push_back([a_IndexBuffer]
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<OpenGLBuffer*>(a_IndexBuffer)->GetID());
		}
	);

}

void tabi::OpenGLCommandList::BindConstantBuffer(Buffer* a_Buffer, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	m_PendingCommands.push_back([a_Buffer, a_Slot]
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, a_Slot, static_cast<OpenGLBuffer*>(a_Buffer)->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindReadWriteBuffer(Buffer* a_Buffer, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	m_PendingCommands.push_back([a_Buffer, a_Slot]
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, a_Slot, static_cast<OpenGLBuffer*>(a_Buffer)->GetID());
		}
	);
}

#undef ENSURE_COMMAND_LIST_IS_RECORDING
