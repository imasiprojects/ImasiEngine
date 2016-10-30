#include "VertexArray.hpp"
#include <GL/glew.h>
#include "../../Utils/OpenglDebugger.hpp"
#include "../../Utils/Preprocessor.hpp"

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

    void VertexArray::draw(VertexArray* vertexArray)
    {
        Buffer* vertexBuffer = vertexArray->getBuffer(Vertex);
        if (vertexBuffer != nullptr)
        {
            glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->getComponentCount());
        }
    }

    VertexArray::VertexArray()
    {
        GL(glGenVertexArrays(1, &_id));
    }

    VertexArray::~VertexArray()
    {
        for (auto& buffer : _buffers)
        {
            safeDelete(buffer.second);
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

}
