#pragma once

#include "GL/glew.h"

namespace ImasiEngine
{
    class Shader
    {
    protected:

        unsigned int _id;

        Shader();
        Shader(const Shader&) = delete;
        Shader(Shader&&) noexcept;
        virtual ~Shader();

        bool compile(const char* shaderSourceCode, GLenum type);

    public:

        unsigned int getId() const;
        bool isValid() const;

    };
}