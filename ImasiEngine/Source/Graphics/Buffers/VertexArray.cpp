#include "VertexArray.hpp"

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

    void VertexArray::attach(Buffer* buffer, BufferType type)
    {
        if (type != Index)
        {
            VertexArray::bind(this);
            {
                GL(glEnableVertexAttribArray(type));

                buffer->bind();
                {
                    GL(glVertexAttribPointer(type, buffer->getMembersPerComponent(), buffer->getGLComponentType(), false, 0, nullptr));
                }
                buffer->unbind();
            }
            VertexArray::unbind();
        }

        _buffers[type] = buffer;
    }

    void VertexArray::detach(BufferType type)
    {
        if (type != Index)
        {
            VertexArray::bind(this);
            {
                GL(glDisableVertexAttribArray(type));
            }
            VertexArray::unbind();
        }

        _buffers.erase(type);
    }

    void VertexArray::render(GLenum drawMode)
    {
        auto indexBuffer = _buffers.find(Index);
        if (indexBuffer != _buffers.end())
        {
            VertexArray::bind(this);
            {
                indexBuffer->second->bind();
                {
                    glDrawElements(drawMode, indexBuffer->second->getComponentCount() * indexBuffer->second->getMembersPerComponent(), indexBuffer->second->getGLComponentType(), nullptr);
                }
                indexBuffer->second->unbind();
            }
            VertexArray::unbind();
        }
        else
        {
            auto vertexBuffer = _buffers.find(Vertex);
            if (vertexBuffer != _buffers.end())
            {
                VertexArray::bind(this);
                {
                    glDrawArrays(drawMode, 0, vertexBuffer->second->getComponentCount());
                }
                VertexArray::unbind();
            }
        }
    }
}
