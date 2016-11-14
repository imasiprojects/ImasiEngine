#ifndef IMASIGAME_VERTEXSHADER_HPP
#define IMASIGAME_VERTEXSHADER_HPP

namespace Shaders
{
    const char* vertexShader = R"SHADER_END(

        #version 330 core

        layout(location = 0) in vec3 vertexPosition_modelspace;
        layout(location = 1) in vec2 vertexUV;

        uniform mat4 MVP;

        out vec2 UV;

        void main()
        {
            UV = vertexUV;
            gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
        }

    )SHADER_END";
}

#endif
