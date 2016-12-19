#include "SimpleRenderer.hpp"

#include "../Programs/VertexShader.hpp"
#include "../Programs/FragmentShader.hpp"

namespace ImasiEngine
{
    const char* SimpleRenderer::_vertexShader = R"SHADER_END(

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

    const char* SimpleRenderer::_fragmentShader = R"SHADER_END(

        #version 330 core

        in vec2 UV;
        out vec3 color;

        uniform sampler2D myTexture;

        void main()
        {
            color = texture(myTexture, UV).rgb;
        }

    )SHADER_END";

    SimpleRenderer::SimpleRenderer()
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

    SimpleRenderer::~SimpleRenderer()
    {
        delete _program;
        delete _vertexArray;
    }

    void SimpleRenderer::clear()
    {
        _entities.clear();
    }

    void SimpleRenderer::add(Entity* entity)
    {
        _entities.push_back(entity);
    }

    void SimpleRenderer::add(std::list<Entity*>& entities)
    {
        _entities.insert(_entities.end(), entities.begin(), entities.end());
    }

    void SimpleRenderer::render(const glm::mat4& VP)
    {
        BIND(Program, _program);
        {
            for (Entity* entity : _entities)
            {
                _program->setUniform("MVP", VP * entity->getModelMatrix());

                BIND(Texture, entity->getModel()->material->diffuseMap, 0);
                {
                    _vertexArray->attachMesh(entity->getModel()->mesh);
                    _vertexArray->render();
                }
                UNBIND(Texture, 0);
            }
        }
        UNBIND(Program);
    }

    void SimpleRenderer::render(Camera& camera)
    {
        render(camera.getViewProjectionMatrix());
    }
}
