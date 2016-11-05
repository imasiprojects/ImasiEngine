#include "VertexArray.hpp"

#include "../../Utils/Opengl.hpp"
#include "../../Utils/Logger.hpp"
#include "ArrayBuffer.hpp"

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
        , _arrayBuffers(vertexArray._arrayBuffers)
    {
        _arrayBuffers.clear();
    }

    VertexArray::~VertexArray()
    {
        _arrayBuffers.clear();
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

    void VertexArray::attachIndexBuffer(IndexBuffer* buffer)
    {
        _indexBuffer = buffer;
    }

    void VertexArray::attachArrayBuffer(ArrayBuffer* buffer, ArrayBufferType type)
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

        _arrayBuffers[type] = buffer;
    }

    void VertexArray::detachIndexBuffer()
    {
        _indexBuffer = nullptr;
    }

    void VertexArray::detachArrayBuffer(ArrayBufferType type)
    {
        VertexArray::bind(this);
        {
            GL(glDisableVertexAttribArray(type));
        }
        VertexArray::unbind();

        _arrayBuffers.erase(type);
    }

    void VertexArray::render(GLenum drawMode)
    {
        if (_indexBuffer != nullptr)
        {
            VertexArray::bind(this);
            {
                _indexBuffer->bind();
                {
                    glDrawElements(drawMode, _indexBuffer->getComponentCount() * _indexBuffer->getMembersPerComponent(), _indexBuffer->getGLComponentType(), nullptr);
                }
                _indexBuffer->unbind();
            }
            VertexArray::unbind();
        }
        else
        {
            auto vertexBuffer = _arrayBuffers.find(Vertex);
            if (vertexBuffer != _arrayBuffers.end())
            {
                VertexArray::bind(this);
                {
                    glDrawArrays(drawMode, 0, vertexBuffer->second->getComponentCount());
                }
                VertexArray::unbind();
            }
            else
            {
                #ifdef DEBUG
                {
                    Logger::out << "Error: Trying to draw non-existing buffer in VAO" << std::endl;
                }
                #endif
            }
        }
    }
}
