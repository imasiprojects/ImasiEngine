#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class VertexShader : public Shader
    {
    protected:

        unsigned int getOpenglShaderType() const override;

    public:

        VertexShader();
        VertexShader(const char* sourceCode);
        VertexShader(const VertexShader&) = delete;
        VertexShader(VertexShader&& shader) noexcept;
        virtual ~VertexShader();
    };
}
