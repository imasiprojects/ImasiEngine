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

    unsigned int VertexShader::getShaderType() const
    {
        return GL_VERTEX_SHADER;
    }

    bool VertexShader::compile(const char* sourceCode)
    {
        bool compilationSuccess = Shader::compile(sourceCode);

        #ifdef DEBUG
        {
            Logger::out << "Vertex shader: " << (compilationSuccess ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return compilationSuccess;
    }
}
