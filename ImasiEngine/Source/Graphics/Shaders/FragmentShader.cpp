#include "FragmentShader.h"

#include "GL/glew.h"
#include "../../Utils/Logger.hpp"

namespace ImasiEngine
{

    FragmentShader::FragmentShader(){}

    FragmentShader::FragmentShader(const char* code)
    {
        load(code);
    }

    FragmentShader::FragmentShader(FragmentShader&& shader) noexcept : Shader(std::move(shader)) {}

    bool FragmentShader::load(const char* code)
    {
        bool result = Shader::load(code, GL_FRAGMENT_SHADER);

        #ifdef DEBUG
        {
            Logger::out << "Fragment shader: " << (result ? "OK" : "ERROR") << std::endl;
        }
        #endif

        return result;
    }

}
