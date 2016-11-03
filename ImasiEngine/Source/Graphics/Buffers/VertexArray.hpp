#pragma once

#include <map>
#include <GL/glew.h>

#include "Buffer.hpp"
#include "BufferType.hpp"

namespace ImasiEngine
{
    class VertexArray : public GpuObject
    {
    private:

        std::map<BufferType, Buffer*> _buffers;
        
    public:

        static void bind(VertexArray* vertexArray);
        static void unbind();

        VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray(VertexArray&& vertexArray) noexcept;
        virtual ~VertexArray();

        void addBuffer(Buffer* buffer, BufferType type);
        void removeBuffer(BufferType type);
        Buffer* getBuffer(BufferType type);

        void draw(BufferType bufferType = Vertex, GLenum drawMode = GL_TRIANGLES);
    };
}
