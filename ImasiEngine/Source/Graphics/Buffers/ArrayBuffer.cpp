#include "ArrayBuffer.hpp"

#include <algorithm>
#include <GL/glew.h>

namespace ImasiEngine
{
    ArrayBuffer::ArrayBuffer(ArrayBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    ArrayBuffer::~ArrayBuffer()
    {
    }

    unsigned int ArrayBuffer::getGLBufferType() const
    {
        return GL_ARRAY_BUFFER;
    }
}
