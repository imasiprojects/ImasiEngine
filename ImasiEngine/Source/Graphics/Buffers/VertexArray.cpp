#include "VertexArray.hpp"

#include "ArrayBuffer.hpp"
#include "../Opengl/OpenglHelper.hpp"
#include "../../Utils/Logger.hpp"

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

    void VertexArray::attachMesh(Mesh* mesh)
    {
        _indexBuffer = mesh->getIndexBuffer();

        ArrayBuffer* meshVertexBuffer = mesh->getVertexBuffer();
        if (meshVertexBuffer != nullptr)
        {
            attachArrayBuffer(meshVertexBuffer, Vertex);
        }
        else
        {
            detachArrayBuffer(Vertex);
        }

        ArrayBuffer* meshUVBuffer = mesh->getUVBuffer();
        if (meshUVBuffer != nullptr)
        {
            attachArrayBuffer(meshUVBuffer, UV);
        }
        else
        {
            detachArrayBuffer(UV);
        }
    }

    void VertexArray::attachIndexBuffer(IndexBuffer* buffer)
    {
        _indexBuffer = buffer;
    }

    void VertexArray::attachArrayBuffer(ArrayBuffer* buffer, ArrayBufferType type, unsigned int divisor)
    {
        BIND(VertexArray, this);
        {
            GL(glEnableVertexAttribArray(type));

            BIND(ArrayBuffer, buffer);
            {
                for (auto& attribute : buffer->getAttributes())
                {
                    GL(glVertexAttribPointer(type, attribute.memberCount, buffer->getGLComponentType(), false, buffer->getComponentSize(), (void*)attribute.offset));
                    GL(glVertexAttribDivisor(type, divisor));
                }
            }
            UNBIND(ArrayBuffer);
        }
        UNBIND(VertexArray);

        _arrayBuffers[type] = buffer;
    }

    void VertexArray::detachIndexBuffer()
    {
        _indexBuffer = nullptr;
    }

    void VertexArray::detachArrayBuffer(ArrayBufferType type)
    {
        BIND(VertexArray, this);
        {
            GL(glDisableVertexAttribArray(type));
        }
        UNBIND(VertexArray);

        _arrayBuffers.erase(type);
    }

    void VertexArray::detachAllBuffers()
    {
        _indexBuffer = nullptr;
        _arrayBuffers.clear();
    }

    void VertexArray::render(GLenum drawMode)
    {
        if (_indexBuffer != nullptr)
        {
            BIND(VertexArray, this);
            {
                BIND(IndexBuffer, _indexBuffer);
                {
                    glDrawElements(drawMode, _indexBuffer->getComponentCount(), _indexBuffer->getGLComponentType(), nullptr);
                }
                UNBIND(IndexBuffer);
            }
            UNBIND(VertexArray);
        }
        else
        {
            auto vertexBuffer = _arrayBuffers.find(Vertex);
            if (vertexBuffer != _arrayBuffers.end())
            {
                BIND(VertexArray, this);
                {
                    glDrawArrays(drawMode, 0, vertexBuffer->second->getComponentCount());
                }
                UNBIND(VertexArray);
            }
            else
            {
                #ifdef DEBUG
                {
                    Logger::out << "Error: Trying to draw VAO without VertexBuffer attached" << std::endl;
                }
                #endif
            }
        }
    }
}
