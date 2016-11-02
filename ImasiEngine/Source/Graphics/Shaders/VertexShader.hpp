#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class VertexShader : public Shader
    {
    public:

        VertexShader();
        VertexShader(const char* sourceCode);
        VertexShader(const VertexShader&) = delete;
        VertexShader(VertexShader&& shader) noexcept;
        ~VertexShader();

        bool compile(const char* sourceCode);
    };
}
