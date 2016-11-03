#pragma once

#include <GL/glew.h>

#include "../GpuObject.hpp"

namespace ImasiEngine
{
    class Shader : public GpuObject
    {
    protected:

        Shader();
        Shader(const Shader&) = delete;
        Shader(Shader&& shader) noexcept;
        virtual ~Shader();

        void createGpuObject() override;
        void destroyGpuObject() override;

        virtual unsigned int getShaderType() const = 0;
        virtual bool compile(const char* sourceCode);
    };
}
