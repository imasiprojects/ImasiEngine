#ifndef IMASIENGINE_VERTEXSHADER_HPP
#define IMASIENGINE_VERTEXSHADER_HPP

#include "Shader.hpp"

namespace ImasiEngine
{
    class VertexShader : public Shader
    {
    protected:

        unsigned int getGLShaderType() const override;

    public:

        VertexShader();
        VertexShader(const char* sourceCode);
        VertexShader(const VertexShader&) = delete;
        VertexShader(VertexShader&& shader) noexcept;
        virtual ~VertexShader();
    };
}

#endif