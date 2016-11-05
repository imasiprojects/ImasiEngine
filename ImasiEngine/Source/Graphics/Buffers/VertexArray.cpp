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
        , _indexBuffer(nullptr)
    {
        VertexArray::createGLObject();
    }

    VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
        : GLObject(std::move(vertexArray))
        , _indexBuffer(vertexArray._indexBuffer)
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

        _buffers[type] = buffer;
    }

    void VertexArray::attach(IndexBuffer* indexBuffer)
    {
        _indexBuffer = indexBuffer;
    }

    void VertexArray::detach(BufferType type)
    {
        VertexArray::bind(this);
        {
            GL(glDisableVertexAttribArray(type));
        }
        VertexArray::unbind();

        _buffers.erase(type);
    }

    void VertexArray::render(GLenum mode)
    {
        VertexArray::bind(this);
        {
            if (_indexBuffer != nullptr)
            {
                _indexBuffer->bind();
                glDrawElements(mode, _indexBuffer->getComponentCount(), _indexBuffer->getGLComponentType(), nullptr);
                _indexBuffer->unbind();
            }
            else
            {
                auto it = _buffers.find(Vertex);
                if (it != _buffers.end())
                {
                    glDrawArrays(mode, 0, it->second->getComponentCount());
                }

            }
        }
        VertexArray::unbind();
    }
}
