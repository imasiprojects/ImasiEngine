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

    unsigned FragmentShader::getShaderType() const
    {
        return GL_FRAGMENT_SHADER;
    }

    bool FragmentShader::compile(const char* sourceCode)
    {
        bool compilationSuccess = Shader::compile(sourceCode);

        #ifdef DEBUG
        {
            Logger::out << "Fragment shader: " << (compilationSuccess ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return compilationSuccess;
    }
}
