#pragma once

#include "Enums/Format.h"

namespace tabi
{
	struct BufferDescription
	{
		EFormat m_Format = EFormat::Unknown;
		size_t m_SizeInBytes = 0;
		uint32_t m_Stride = 0;

		// TODO: Something about usage
		// OGL needs this when creating the buffer (glBufferData)
		// Might be related to this in D3D12? https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_heap_properties
	};

	class Buffer
	{
	public:
		inline EFormat GetFormat() const { return m_Format; }
		inline size_t GetSize() const { return m_Size; }
		inline uint32_t GetStride() const { return m_Stride; }

	protected:
		Buffer(EFormat a_Format, size_t a_BufferSize, uint32_t a_Stride)
			: m_Format(a_Format), m_Size(a_BufferSize), m_Stride(a_Stride)
		{}

	private:
		EFormat m_Format = EFormat::Unknown;
		size_t m_Size = 0;
		uint32_t m_Stride = 0;
	};
}
