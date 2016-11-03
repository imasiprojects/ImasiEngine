#include "FragmentShader.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"

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

    unsigned FragmentShader::getOpenglShaderType() const
    {
        return GL_FRAGMENT_SHADER;
    }
}
