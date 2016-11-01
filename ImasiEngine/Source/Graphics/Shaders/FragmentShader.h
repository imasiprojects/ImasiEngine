#pragma once

#include "Shader.hpp"

namespace ImasiEngine
{
    class FragmentShader : public Shader
    {
    public:
        FragmentShader();
        FragmentShader(const char* code);
        FragmentShader(const FragmentShader&) = delete;
        FragmentShader(FragmentShader&& shader) noexcept;

        bool load(const char* code);
    };
}
