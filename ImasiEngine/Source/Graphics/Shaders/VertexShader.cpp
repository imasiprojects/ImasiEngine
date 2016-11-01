#include "VertexShader.hpp"

#include "GL/glew.h"
#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{

    VertexShader::VertexShader(){}
    VertexShader::VertexShader(const char* code)
    {
        load(code);
    }

    VertexShader::VertexShader(VertexShader&& shader) noexcept : Shader(std::move(shader)){}

    bool VertexShader::load(const char* code)
    {
        bool result = Shader::load(code, GL_VERTEX_SHADER);

        #ifdef DEBUG
        {
            Logger::out << "Vertex shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return result;
    }

}
