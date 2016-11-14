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

        static char* _fragmentShader;
        static char* _vertexShader;

    protected:
        
        Program* _program;
        VertexArray* _vertexArray;

    public:

        Simple3DRenderer();
        ~Simple3DRenderer();

        void render(glm::mat4& VP) const override;
    };
}

#endif
