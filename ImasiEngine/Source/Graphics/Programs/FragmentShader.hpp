#ifndef IMASIENGINE_FRAGMENTSHADER_HPP
#define IMASIENGINE_FRAGMENTSHADER_HPP

#include "Shader.hpp"
#include "../Opengl/Enums/ShaderType.hpp"

namespace ImasiEngine
{
    class FragmentShader
        : public Shader
    {
    protected:

        GLEnums::ShaderType getGLShaderType() const override;

    public:

        FragmentShader();
        FragmentShader(const char* sourceCode);
        FragmentShader(const FragmentShader&) = delete;
        FragmentShader(FragmentShader&& shader) noexcept;
        virtual ~FragmentShader();
    };
}

#endif
