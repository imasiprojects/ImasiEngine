#ifndef IMASIENGINE_SHADER_HPP
#define IMASIENGINE_SHADER_HPP

#include "../GLObject.hpp"

namespace ImasiEngine
{
    class Shader : public GLObject
    {
    protected:

        Shader();
        Shader(const Shader&) = delete;
        Shader(Shader&& shader) noexcept;
        virtual ~Shader();

        void createGLObject() override;
        void destroyGLObject() override;

        virtual unsigned int getGLShaderType() const = 0;

    public:

        virtual bool compile(const char* sourceCode);
    };
}

#endif
