#include "Mesh.hpp"

namespace ImasiEngine
{
    Mesh::Mesh(Mesh&& mesh) noexcept
        : _indexBuffer(std::move(mesh._indexBuffer))
        , _vertexBuffer(std::move(mesh._vertexBuffer))
        , _uvBuffer(std::move(mesh._uvBuffer))
    {
    }

    IndexBuffer* Mesh::getIndexBuffer() const
    {
        return _indexBuffer.get();
    }

    void Mesh::setIndexBuffer(IndexBuffer&& indexBuffer)
    {
        _indexBuffer = std::make_unique<IndexBuffer>(std::move(indexBuffer));
    }

    void Mesh::removeIndexBuffer()
    {
        _indexBuffer = nullptr;
    }

    ArrayBuffer* Mesh::getVertexBuffer() const
    {
        return _vertexBuffer.get();
    }

    void Mesh::setVertexBuffer(ArrayBuffer&& vertexBuffer)
    {
        _vertexBuffer = std::make_unique<ArrayBuffer>(std::move(vertexBuffer));
    }

    void Mesh::removeVertexBuffer()
    {
        _vertexBuffer = nullptr;
    }

    ArrayBuffer* Mesh::getUVBuffer() const
    {
        return _uvBuffer.get();
    }

    void Mesh::setUVBuffer(ArrayBuffer&& uvBuffer)
    {
        _uvBuffer = std::make_unique<ArrayBuffer>(std::move(uvBuffer));
    }
    void Mesh::removeUVBuffer()
    {
        _uvBuffer = nullptr;
    }
}
