#pragma once

#include <map>

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
        static void draw(VertexArray* vertexArray);

        VertexArray();
        ~VertexArray();

        void addBuffer(Buffer* buffer, BufferType type);
        Buffer* getBuffer(BufferType type);
    };
}
