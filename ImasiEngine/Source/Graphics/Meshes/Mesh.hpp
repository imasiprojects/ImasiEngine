#ifndef IMASIENGINE_MESH_HPP
#define IMASIENGINE_MESH_HPP

#include "../Buffers/ArrayBuffer.hpp"
#include "../Buffers/IndexBuffer.hpp"

namespace ImasiEngine
{
    class Mesh
    {
    private:

        IndexBuffer* _indexBuffer;
        ArrayBuffer* _vertexBuffer;
        ArrayBuffer* _uvBuffer;

    public:

        Mesh();
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&& mesh) noexcept;
        ~Mesh();

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
