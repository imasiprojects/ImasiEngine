#ifndef IMASIGAME_FRAGMENTSHADER_HPP
#define IMASIGAME_FRAGMENTSHADER_HPP

namespace Shaders
{
    const char* fragmentShader = R"SHADER_END(

        #version 330 core

        in vec2 UV;
        out vec3 color;

        uniform sampler2D myTexture;

        void main()
        {
            color = texture(myTexture, UV).rgb;
        }

    )SHADER_END";
}

#endif
