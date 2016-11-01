#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class VertexShader : public Shader
    {
    public:

        VertexShader();
        VertexShader(const char* shaderSourceCode);
        VertexShader(const VertexShader&) = delete;
        VertexShader(VertexShader&& shader) noexcept;

        bool compile(const char* code);
    };
}
