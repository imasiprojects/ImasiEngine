#include "VertexArray.hpp"
#include <GL/glew.h>
#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void VertexArray::bind(VertexArray* vertexArray)
    {
        GL(glBindVertexArray(vertexArray->_id));
    }

    void VertexArray::unbind()
    {
        GL(glBindVertexArray(UNBIND));
    }

    VertexArray::VertexArray()
        : GpuObject()
    {
        GL(glGenVertexArrays(1, &_id));
    }

    VertexArray::~VertexArray()
    {
        for (auto& buffer : _buffers)
        {
            delete buffer.second;
        }

        GL(glDeleteVertexArrays(1, &_id));
    }

    void VertexArray::addBuffer(Buffer* buffer, BufferType type)
    {
        VertexArray::bind(this);
        Buffer::bind(buffer);

        GL(glEnableVertexAttribArray(type));
        GL(glVertexAttribPointer(type, buffer->getMembersPerComponent(), GL_FLOAT, false, 0, nullptr));

        Buffer::unbind();
        VertexArray::unbind();

        removeBuffer(type);
        _buffers[type] = buffer;
    }

    void VertexArray::removeBuffer(BufferType type)
    {
        auto it = _buffers.find(type);
        if (it != _buffers.end())
        {
            delete it->second;
            _buffers.erase(it);
        }
    }

    Buffer* VertexArray::getBuffer(BufferType type)
    {
        auto it = _buffers.find(type);
        if (it != _buffers.end())
        {
            return it->second;
        }

        return nullptr;
    }

    void VertexArray::draw(BufferType bufferType, GLenum mode)
    {
        VertexArray::bind(this);

        Buffer* vertexBuffer = this->getBuffer(bufferType);
        if (vertexBuffer != nullptr)
        {
            GL(glDrawArrays(mode, 0, vertexBuffer->getComponentCount()));
        }

        VertexArray::unbind();
    }
}
