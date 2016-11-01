#include "FragmentShader.hpp"

#include <GL/glew.h>

#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{

    FragmentShader::FragmentShader()
    {
        
    }

    FragmentShader::FragmentShader(const char* shaderSourceCode)
    {
        compile(shaderSourceCode);
    }

    FragmentShader::FragmentShader(FragmentShader&& shader) noexcept : Shader(std::move(shader)) {}

    bool FragmentShader::compile(const char* code)
    {
        bool result = Shader::compile(code, GL_FRAGMENT_SHADER);

        #ifdef DEBUG
        {
            Logger::out << "Fragment shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return result;
    }

}
