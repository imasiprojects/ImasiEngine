#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class FragmentShader : public Shader
    {
    public:

        FragmentShader();
        FragmentShader(const char* shaderSourceCode);
        FragmentShader(const FragmentShader&) = delete;
        FragmentShader(FragmentShader&& shader) noexcept;

        bool compile(const char* code);
    };
}
