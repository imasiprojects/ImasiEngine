#ifndef IMASIENGINE_MESH_HPP
#define IMASIENGINE_MESH_HPP

#include "../Buffers/ArrayBuffer.hpp"
#include "../Buffers/IndexBuffer.hpp"

namespace ImasiEngine
{
    class Mesh
    {
    private:

        std::unique_ptr<IndexBuffer> _indexBuffer;
        std::unique_ptr<ArrayBuffer> _vertexBuffer;
        std::unique_ptr<ArrayBuffer> _uvBuffer;

    public:

        Mesh() = default;
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&& mesh) noexcept;

        IndexBuffer* getIndexBuffer() const;
        void setIndexBuffer(IndexBuffer&& indexBuffer);
        void removeIndexBuffer();

        ArrayBuffer* getVertexBuffer() const;
        void setVertexBuffer(ArrayBuffer&& vertexBuffer);
        void removeVertexBuffer();

        ArrayBuffer* getUVBuffer() const;
        void setUVBuffer(ArrayBuffer&& uvBuffer);
        void removeUVBuffer();
    };
}

#endif
