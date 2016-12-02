#ifndef IMASIENGINE_VERTEXARRAY_HPP
#define IMASIENGINE_VERTEXARRAY_HPP

#include <map>

#include <GL/glew.h>

#include "ArrayBuffer.hpp"
#include "ArrayBufferType.hpp"
#include "IndexBuffer.hpp"
#include "../Meshes/Mesh.hpp"

namespace ImasiEngine
{
    class VertexArray : public GLObject
    {
    private:

        IndexBuffer* _indexBuffer;
        std::map<ArrayBufferType, ArrayBuffer*> _arrayBuffers;

    protected:

        void createGLObject() override;
        void destroyGLObject() override;
        
    public:

        static void bind(VertexArray* vertexArray);
        static void unbind();

        VertexArray();
        VertexArray(const VertexArray&) = delete;
        VertexArray(VertexArray&& vertexArray) noexcept;
        virtual ~VertexArray();

        void attachMesh(Mesh* mesh);

        void attachIndexBuffer(IndexBuffer* buffer);
        void detachIndexBuffer();

        void attachArrayBuffer(ArrayBuffer* buffer, ArrayBufferType type);
        void detachArrayBuffer(ArrayBufferType type);

        void detachAllBuffers();

        void render(GLenum drawMode = GL_TRIANGLES);
    };
}

#endif
