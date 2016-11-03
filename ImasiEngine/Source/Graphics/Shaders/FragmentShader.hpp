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
        virtual ~FragmentShader();

        unsigned int getShaderType() const override;
        bool compile(const char* sourceCode) override;
    };
}
