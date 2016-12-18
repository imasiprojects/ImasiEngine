#include "IndexBuffer.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    void IndexBuffer::bind(IndexBuffer* buffer)
    {
        GL(glBindBuffer(getEnumValue(GlBufferType::IndexBuffer), buffer->getGLObjectId()));
    }

    void IndexBuffer::unbind()
    {
        GL(glBindBuffer(getEnumValue(GlBufferType::IndexBuffer), NULL_ID));
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& buffer) noexcept
        : Buffer(std::move(buffer))
    {
    }

    IndexBuffer::~IndexBuffer()
    {
    }
}
