#include "FragmentShader.hpp"

#include "../../Utils/Logger.hpp"
#include "../Opengl/Enums/ShaderType.hpp"

namespace ImasiEngine
{
    FragmentShader::FragmentShader()
        : Shader()
    {
    }

    FragmentShader::FragmentShader(const char* sourceCode)
        : Shader()
    {
        FragmentShader::compile(sourceCode);
    }

    FragmentShader::FragmentShader(FragmentShader&& shader) noexcept
        : Shader(std::move(shader))
    {
    }

    FragmentShader::~FragmentShader()
    {
    }

    GLEnums::ShaderType FragmentShader::getGLShaderType() const
    {
        return GLEnums::ShaderType::Fragment;
    }
}
