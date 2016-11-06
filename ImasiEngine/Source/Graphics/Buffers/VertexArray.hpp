#pragma once

#include <map>

#include <GL/glew.h>

#include "ArrayBuffer.hpp"
#include "ArrayBufferType.hpp"
#include "IndexBuffer.hpp"

namespace ImasiEngine
{
    class VertexArray : public GLObject
    {
    private:

        IndexBuffer* _indexBuffer;
        std::map<ArrayBufferType, ArrayBuffer*> _arrayBuffers;
        
    public:

        static void bind(VertexArray* vertexArray);
        static void unbind();

        VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray(VertexArray&& vertexArray) noexcept;
        virtual ~VertexArray();

        void createGLObject() override;
        void destroyGLObject() override;

        void detachAllBuffers();

        void attachIndexBuffer(IndexBuffer* buffer);
        void detachIndexBuffer();

        void attachArrayBuffer(ArrayBuffer* buffer, ArrayBufferType type);
        void detachArrayBuffer(ArrayBufferType type);

        void render(GLenum drawMode = GL_TRIANGLES);
    };
}
