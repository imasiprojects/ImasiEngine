#ifndef IMASIGAME_VERTEXSHADER_HPP
#define IMASIGAME_VERTEXSHADER_HPP

namespace Shaders
{
    const char* vertexShader = R"SHADER_END(

        #version 330 core

        layout(location = 0) in vec3 vertexPosition_modelspace;
        layout(location = 1) in vec2 vertexUV;

        out vec2 UV;

        void main()
        {
            gl_Position = vec4(vertexPosition_modelspace, 1);
            UV = vertexUV;
        }

    )SHADER_END";
}

#endif
