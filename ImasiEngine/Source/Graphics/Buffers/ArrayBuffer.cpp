#include "ArrayBuffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void ArrayBuffer::bind(ArrayBuffer* buffer)
    {
        GL(glBindBuffer(GLEnums::BufferType::Array, buffer->getGLObjectId()));
    }

    void ArrayBuffer::unbind()
    {
        GL(glBindBuffer(GLEnums::BufferType::Array, NULL_ID));
    }

    ArrayBuffer::ArrayBuffer(ArrayBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    ArrayBuffer::~ArrayBuffer()
    {
    }
}
