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
        Shader(Shader&&);
        virtual ~Shader();

        bool load(const char* code, GLenum type);

    public:

        unsigned int getId() const;

    };
}