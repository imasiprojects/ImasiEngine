#include "VertexShader.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    VertexShader::VertexShader()
        : Shader()
    {
    }

    VertexShader::VertexShader(const char* sourceCode)
        : Shader()
    {
        VertexShader::compile(sourceCode);
    }

    VertexShader::VertexShader(VertexShader&& shader) noexcept
        : Shader(std::move(shader))
    {
    }

    VertexShader::~VertexShader()
    {
    }

    unsigned int VertexShader::getOpenglShaderType() const
    {
        return GL_VERTEX_SHADER;
    }
}
