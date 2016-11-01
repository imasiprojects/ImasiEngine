#pragma once

#include "Shaders/Shader.hpp"

namespace ImasiEngine
{
    class Program
    {
        unsigned int _id;
        bool _isLinked;

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

        unsigned int getId() const;
        bool isLinked() const;
    };
}

