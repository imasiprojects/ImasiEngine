#pragma once

#include <GL/glew.h>

#include "../GpuObject.hpp"

namespace ImasiEngine
{
    class Shader : public GpuObject
    {
    protected:

        Shader();
        Shader(const Shader& shader) = delete;
        Shader(Shader&& shader) noexcept;
        virtual ~Shader();

        bool compile(const char* sourceCode, GLenum type);
    };
}
