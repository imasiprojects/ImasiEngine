#pragma once

namespace ImasiEngine
{
    class Shader
    {
    private:

        unsigned int _id;

    public:

        static void bind(Shader* shader);
        static void unbind();

        Shader();
        ~Shader();

        bool loadFromStrings(const char* vertexShader, const char* fragmentShader);
    };
}