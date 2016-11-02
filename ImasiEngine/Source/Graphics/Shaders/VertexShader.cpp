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
    {
        compile(sourceCode);
    }

    VertexShader::VertexShader(VertexShader&& shader) noexcept
        : Shader(std::move(shader))
    {
    }

    VertexShader::~VertexShader()
    {
    }

    bool VertexShader::compile(const char* sourceCode)
    {
        bool result = Shader::compile(sourceCode, GL_VERTEX_SHADER);

        #ifdef DEBUG
        {
            Logger::out << "Vertex shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return result;
    }
}
