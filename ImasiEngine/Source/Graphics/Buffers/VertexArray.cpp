#include "VertexArray.hpp"
#include <GL/glew.h>
#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    void VertexArray::bind(VertexArray* vertexArray)
    {
        GL(glBindVertexArray(vertexArray->getGLObjectId()));
    }

    void VertexArray::unbind()
    {
        GL(glBindVertexArray(NULL_ID));
    }

    VertexArray::VertexArray()
        : GLObject()
    {
        VertexArray::createGLObject();
    }

    VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
        : GLObject(std::move(vertexArray))
        , _buffers(vertexArray._buffers)
    {
        _buffers.clear();
    }

    VertexArray::~VertexArray()
    {
        _buffers.clear();
        VertexArray::destroyGLObject();
    }

    void VertexArray::createGLObject()
    {
        unsigned int id;
        GL(glGenVertexArrays(1, &id));

        setGLObjectId(id);
    }

    void VertexArray::destroyGLObject()
    {
        unsigned int id = getGLObjectId();
        GL(glDeleteVertexArrays(1, &id));

        unsetGLObjectId();
    }

    void VertexArray::attachBuffer(Buffer* buffer, BufferType type)
    {
        VertexArray::bind(this);
        {
            GL(glEnableVertexAttribArray(type));

            Buffer::bind(buffer);
            {
                GL(glVertexAttribPointer(type, buffer->getMembersPerComponent(), GL_FLOAT, false, 0, nullptr));
            }
            Buffer::unbind();
        }
        VertexArray::unbind();

        _buffers[type] = buffer;
    }

    void VertexArray::detachBuffer(BufferType type)
    {
        VertexArray::bind(this);
        {
            GL(glDisableVertexAttribArray(type));
        }
        VertexArray::unbind();

        _buffers.erase(type);
    }

    void VertexArray::draw(BufferType bufferType, GLenum mode)
    {
        VertexArray::bind(this);
        {
            auto it = _buffers.find(bufferType);
            if (it != _buffers.end())
            {
                glDrawArrays(mode, 0, it->second->getComponentCount());
            }
        }
        VertexArray::unbind();
    }
}
