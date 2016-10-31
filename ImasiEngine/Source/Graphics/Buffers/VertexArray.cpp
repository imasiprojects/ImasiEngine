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
        GL(glBindVertexArray(0));
    }

    VertexArray::VertexArray()
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
        bind(this);
        Buffer::bind(buffer);

        GL(glEnableVertexAttribArray(type));
        GL(glVertexAttribPointer(type, buffer->getMembersPerComponent(), GL_FLOAT, false, 0, nullptr));

        Buffer::unbind();
        unbind();

        _buffers[type] = buffer;
    }

    Buffer* VertexArray::getBuffer(BufferType type)
    {
        if (_buffers.find(type) != _buffers.end())
        {
            return _buffers[type];
        }

        return nullptr;
    }


    void VertexArray::draw(BufferType bufferType, GLenum mode)
    {
        VertexArray::bind(this);

        Buffer* vertexBuffer = this->getBuffer(bufferType);
        if (vertexBuffer != nullptr)
        {
            glDrawArrays(mode, 0, vertexBuffer->getComponentCount());
        }
    }
}
