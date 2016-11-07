#include "Mesh.hpp"

namespace ImasiEngine
{
    Mesh::Mesh()
        : _indexBuffer(nullptr)
        , _vertexBuffer(nullptr)
        , _uvBuffer(nullptr)
    {
    }

    Mesh::~Mesh()
    {
        delete _indexBuffer;
        delete _vertexBuffer;
        delete _uvBuffer;
    }

    IndexBuffer* Mesh::getIndexBuffer() const
    {
        return _indexBuffer;
    }

    void Mesh::setIndexBuffer(IndexBuffer&& indexBuffer)
    {
        delete _indexBuffer;
        _indexBuffer = new IndexBuffer(std::move(indexBuffer));
    }

    ArrayBuffer* Mesh::getVertexBuffer() const
    {
        return _vertexBuffer;
    }

    void Mesh::setVertexBuffer(ArrayBuffer&& vertexBuffer)
    {
        delete _vertexBuffer;
        _vertexBuffer = new ArrayBuffer(std::move(vertexBuffer));
    }

    ArrayBuffer* Mesh::getUVBuffer() const
    {
        return _uvBuffer;
    }

    void Mesh::setUVBuffer(ArrayBuffer&& uvBuffer)
    {
        delete _uvBuffer;
        _uvBuffer = new ArrayBuffer(std::move(uvBuffer));
    }
}
