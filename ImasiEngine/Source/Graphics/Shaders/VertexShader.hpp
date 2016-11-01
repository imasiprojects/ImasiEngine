#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class VertexShader : public Shader
    {
    public:
        VertexShader();
        VertexShader(const char* code);
        VertexShader(const VertexShader&) = delete;
        VertexShader(VertexShader&& shader) noexcept;

        bool load(const char* code);
    };
}
