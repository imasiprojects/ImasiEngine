#include "Simple3DRenderer.hpp"

#include "../Shaders/VertexShader.hpp"
#include "../Shaders/FragmentShader.hpp"

namespace ImasiEngine
{
    const char* Simple3DRenderer::_vertexShader = R"SHADER_END(

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

    const char* Simple3DRenderer::_fragmentShader = R"SHADER_END(

        #version 330 core

        in vec2 UV;
        out vec3 color;

        uniform sampler2D myTexture;

        void main()
        {
            color = texture(myTexture, UV).rgb;
        }

    )SHADER_END";

    Simple3DRenderer::Simple3DRenderer()
        : Renderer()
        , _program(new Program())
        , _vertexArray(new VertexArray())
    {
        VertexShader vertexShader(_vertexShader);
        FragmentShader fragmentShader(_fragmentShader);

        _program->attach(vertexShader);
        _program->attach(fragmentShader);
        if (!_program->link())
        {
            Logger::out << "Error linking program" << std::endl;
        }
    }

    Simple3DRenderer::~Simple3DRenderer()
    {
        delete _program;
        delete _vertexArray;
    }

    void Simple3DRenderer::render(Camera& camera) const
    {
        glm::mat4 VP = camera.matrix();

        BIND(Program, _program);
        {
            for (Entity* entity : _entities)
            {
                _program->setUniform("MVP", VP * entity->getModelMatrix());

                BIND(Texture, entity->model->material->diffuseMap, 0);
                {
                    _vertexArray->attachMesh(entity->model->mesh);
                    _vertexArray->render();
                }
                UNBIND(Texture, 0);
            }
        }
        UNBIND(Program);
    }
}
