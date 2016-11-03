#pragma once

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

        virtual unsigned int getOpenglShaderType() const = 0;

    public:

        virtual bool compile(const char* sourceCode);
    };
}
