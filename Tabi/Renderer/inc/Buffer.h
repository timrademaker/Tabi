#pragma once

#include "Enums/BufferEnums.h"
#include "Enums/Format.h"

#include <TabiMacros.h>

namespace tabi
{
	struct BufferDescription
	{
		EFormat m_Format = EFormat::Unknown;
		EBufferRole m_Role = EBufferRole::Vertex;
		size_t m_SizeInBytes = 0;
		uint32_t m_Stride = 0;

		// TODO: Something about usage
		// OGL needs this when creating the buffer (glBufferData)
		// Might be related to this in D3D12? https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_heap_properties
	};

	class Buffer
	{
	public:
		TABI_NO_COPY(Buffer);
		TABI_NO_MOVE(Buffer);

		inline const BufferDescription& GetBufferDescription() const
		{
			return m_BufferDescription;
		}

		inline size_t GetBufferSize() const
		{
			return m_BufferDescription.m_SizeInBytes;
		}

	protected:
		Buffer(BufferDescription a_BufferDescription)
			: m_BufferDescription(a_BufferDescription)
		{}
		~Buffer() = default;

	private:
		BufferDescription m_BufferDescription{};
	};
}
