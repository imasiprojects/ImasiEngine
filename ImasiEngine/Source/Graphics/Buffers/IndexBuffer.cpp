#include "IndexBuffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void IndexBuffer::bind(IndexBuffer* buffer)
    {
        GL(glBindBuffer(GLEnums::BufferType::IndexBuffer, buffer->getGLObjectId()));
    }

    void IndexBuffer::unbind()
    {
        GL(glBindBuffer(GLEnums::BufferType::IndexBuffer, NULL_ID));
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    IndexBuffer::~IndexBuffer()
    {
    }
}
