#pragma once

#include "Shaders/Shader.hpp"

namespace ImasiEngine
{
    class Program : GpuObject
    {
    private:

        bool _isLinked;
        bool _invalidAttachPerformed;

    public:

        static void bind(Program* program);
        static void unbind();

        Program();
        Program(const Program&) = delete;
        Program(Program&& program) noexcept;
        ~Program();

        void attach(const Shader& shader);
        void detach(const Shader& shader);
        bool link();

        void reset();

        bool isLinked() const;
        bool invalidAttachPerformed() const;
    };
}
