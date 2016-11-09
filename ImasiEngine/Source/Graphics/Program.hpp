#ifndef IMASIENGINE_PROGRAM_HPP
#define IMASIENGINE_PROGRAM_HPP

#include "Shaders/Shader.hpp"
#include "GLObject.hpp"

namespace ImasiEngine
{
    class Program : public GLObject
    {
    private:

        bool _isLinked;
        bool _invalidAttachPerformed;

    protected:

        void createGLObject() override;
        void destroyGLObject() override;

    public:

        static void bind(Program* program);
        static void unbind();

        Program();
        Program(const Program&) = delete;
        Program(Program&& program) noexcept;
        virtual ~Program();

        bool isLinked() const;
        bool invalidAttachPerformed() const;

        void attach(const Shader& shader);
        void detach(const Shader& shader);
        bool link();

        void reset();
    };
}

#endif
