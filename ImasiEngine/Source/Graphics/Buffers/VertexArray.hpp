#pragma once

#include <map>

#include <GL/glew.h>

#include "Buffer.hpp"
#include "BufferType.hpp"
#include "IndexBuffer.hpp"

namespace ImasiEngine
{
    class VertexArray : public GLObject
    {
    private:

        IndexBuffer* _indexBuffer;
        std::map<BufferType, Buffer*> _buffers;
        
    public:

        static void bind(VertexArray* vertexArray);
        static void unbind();

        VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray(VertexArray&& vertexArray) noexcept;
        virtual ~VertexArray();

        void createGLObject() override;
        void destroyGLObject() override;

        void attach(Buffer* buffer, BufferType type);
        void attach(IndexBuffer* buffer);
        void detach(BufferType type);

        void render(GLenum drawMode = GL_TRIANGLES);
    };
}
