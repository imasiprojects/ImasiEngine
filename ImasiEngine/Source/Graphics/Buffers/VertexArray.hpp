#pragma once

#include <map>
#include <GL/glew.h>

#include "Buffer.hpp"
#include "BufferType.hpp"

namespace ImasiEngine
{
    class VertexArray
    {
    private:

        unsigned int _id;
        std::map<BufferType, Buffer*> _buffers;
        
    public:

        static void bind(VertexArray* vertexArray);
        static void unbind();

        VertexArray();
        ~VertexArray();

        void addBuffer(Buffer* buffer, BufferType type);
        void removeBuffer(BufferType type);
        Buffer* getBuffer(BufferType type);

        void draw(BufferType bufferType = Vertex, GLenum drawMode = GL_TRIANGLES);
    };
}
