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
    {
        compile(sourceCode);
    }

    FragmentShader::FragmentShader(FragmentShader&& shader) noexcept
        : Shader(std::move(shader))
    {
    }

    FragmentShader::~FragmentShader()
    {
    }

    bool FragmentShader::compile(const char* sourceCode)
    {
        bool result = Shader::compile(sourceCode, GL_FRAGMENT_SHADER);

        #ifdef DEBUG
        {
            Logger::out << "Fragment shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return result;
    }
}
