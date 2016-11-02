#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class FragmentShader : public Shader
    {
    public:

        FragmentShader();
        FragmentShader(const char* sourceCode);
        FragmentShader(const FragmentShader&) = delete;
        FragmentShader(FragmentShader&& shader) noexcept;
        ~FragmentShader();

        bool compile(const char* code);
    };
}
