#include "VertexShader.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{
    VertexShader::VertexShader()
    {
        
    }

    VertexShader::VertexShader(const char* shaderSourceCode)
    {
        compile(shaderSourceCode);
    }

    VertexShader::VertexShader(VertexShader&& shader) noexcept : Shader(std::move(shader)){}

    bool VertexShader::compile(const char* code)
    {
        bool result = Shader::compile(code, GL_VERTEX_SHADER);

        #ifdef DEBUG
        {
            Logger::out << "Vertex shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return result;
    }

}
