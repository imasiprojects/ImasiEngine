#pragma once

namespace Shaders
{
    const char* fragmentShader = R"SHADER_END(

    #version 330 core

    out vec3 color;

    void main()
    {
        color = vec3(1,0,0);
    }

)SHADER_END";
}