#include "ArrayBuffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void ArrayBuffer::bind(ArrayBuffer* buffer)
    {
        GL(glBindBuffer(_glBufferType, buffer->getGLObjectId()));
    }

    void ArrayBuffer::unbind()
    {
        GL(glBindBuffer(_glBufferType, NULL_ID));
    }

    ArrayBuffer::ArrayBuffer(ArrayBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    ArrayBuffer::~ArrayBuffer()
    {
    }
}
