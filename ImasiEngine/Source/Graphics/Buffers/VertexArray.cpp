#include "VertexArray.hpp"

#include <GL/glew.h>

#include "ArrayBuffer.hpp"
#include "../Opengl/OpenglHelper.hpp"
#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    void VertexArray::bind(const VertexArray& vertexArray)
    {
        GL(glBindVertexArray(vertexArray.getGLObjectId()));
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
        {
            auto vertexArrayBindGuard = OpenglHelper::makeBindGuard(*this);
            auto arrayBufferBindGuard = OpenglHelper::makeBindGuard(*buffer);
            unsigned int offset = 0;

            for (auto& attribute : buffer->getAttributes())
            {
                GL(glEnableVertexAttribArray(type + offset));
                GL(glVertexAttribPointer(type + offset, attribute.memberCount, buffer->getGLComponentType(), false, buffer->getComponentSize(), (void*)attribute.offset));
                GL(glVertexAttribDivisor(type + offset, divisor));

                offset++;
            }
        }

        _arrayBuffers[type] = buffer;
    }

    void VertexArray::detachIndexBuffer()
    {
        _indexBuffer = nullptr;
    }

    void VertexArray::detachArrayBuffer(ArrayBufferType type)
    {
        const auto& bufferIterator = _arrayBuffers.find(type);

        if (bufferIterator != _arrayBuffers.end())
        {
            {
                auto bindGuard = OpenglHelper::makeBindGuard(*this);

                for (unsigned int i = 0; i < bufferIterator->second->getAttributes().size(); i++)
                {
                    GL(glDisableVertexAttribArray(type + i));
                }
            }

            _arrayBuffers.erase(bufferIterator);
        }
    }

    void VertexArray::detachAllBuffers()
    {
        _indexBuffer = nullptr;
        _arrayBuffers.clear();
    }

    void VertexArray::render(GLEnums::DrawMode drawMode)
    {
        ArrayBuffer* modelMatrixBuffer = _arrayBuffers[ModelMatrix];

        if (_indexBuffer != nullptr)
        {
            auto vertexArrayBindGuard = OpenglHelper::makeBindGuard(*this);
            auto indexBufferBindGuard = OpenglHelper::makeBindGuard(*_indexBuffer);

            if (modelMatrixBuffer != nullptr)
            {
                glDrawElementsInstanced(drawMode, _indexBuffer->getComponentCount() * _indexBuffer->getComponentMemberCount(), _indexBuffer->getGLComponentType(), nullptr, modelMatrixBuffer->getComponentCount());
            }
            else
            {
                glDrawElements(drawMode, _indexBuffer->getComponentCount() * _indexBuffer->getComponentMemberCount(), _indexBuffer->getGLComponentType(), nullptr);
            }
        }
        else
        {
            const auto& vertexBufferIterator = _arrayBuffers.find(Vertex);
            if (vertexBufferIterator != _arrayBuffers.end())
            {
                ArrayBuffer* vertexBuffer = vertexBufferIterator->second;
                auto bindGuard = OpenglHelper::makeBindGuard(*this);

                if (modelMatrixBuffer != nullptr)
                {
                    glDrawElementsInstanced(drawMode, vertexBuffer->getComponentCount() * vertexBuffer->getComponentMemberCount(), vertexBuffer->getGLComponentType(), nullptr, modelMatrixBuffer->getComponentCount());
                }
                else
                {
                    glDrawArrays(drawMode, 0, vertexBuffer->getComponentCount() * vertexBuffer->getComponentMemberCount());
                }
            }
            else
            {
                // TODO: Exception :O

                #ifdef DEBUG
                {
                    Logger::out << "Error: Trying to draw VAO without VertexBuffer attached" << std::endl;
                }
                #endif
            }
        }
    }
}
