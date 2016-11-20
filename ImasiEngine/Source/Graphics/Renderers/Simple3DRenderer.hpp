#ifndef IMASIENGINE_SIMPLE3DRENDERER_HPP
#define IMASIENGINE_SIMPLE3DRENDERER_HPP

#include "Renderer.hpp"
#include "../Program.hpp"
#include "../Buffers/VertexArray.hpp"

namespace ImasiEngine
{
    class Simple3DRenderer
        : public Renderer
    {
    private:

        static const char* _fragmentShader;
        static const char* _vertexShader;

    protected:
        
        Program* _program;
        VertexArray* _vertexArray;

    public:

        Simple3DRenderer();
        ~Simple3DRenderer();

        void render(glm::mat4& vp) const override;
        void render(Camera& camera) const;
    };
}

#endif
