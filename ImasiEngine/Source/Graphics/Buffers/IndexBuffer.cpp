#include "IndexBuffer.hpp"

#include <algorithm>
#include <GL/glew.h>

namespace ImasiEngine
{
    IndexBuffer::IndexBuffer(unsigned int* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer()
    {
        initBufferData(data, componentCount, membersPerComponent);
    }

    IndexBuffer::IndexBuffer(unsigned short* data, unsigned int componentCount, unsigned int membersPerComponent)
        : Buffer()
    {
        initBufferData(data, componentCount, membersPerComponent);
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    IndexBuffer::~IndexBuffer()
    {
    }

    unsigned int IndexBuffer::getGLBufferType() const
    {
        return GL_ELEMENT_ARRAY_BUFFER;
    }
}
