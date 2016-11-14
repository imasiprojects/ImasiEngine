#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Utils/Logger.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/FragmentShader.hpp"
#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Utils/Opengl.hpp"
#include "../../../ImasiEngine/Source/DeleteMe/MeshLoader.hpp"
#include <glm/gtc/matrix_transform.inl>

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context)
        : Scene()
        , _context(context)
        , _vertexArray(new VertexArray())
        , _program(new Program())
        , _material(new Material())
        , _model(new Model())
        , _entity(new Entity())
    {
        // TEST
        {
            GL(GL(glDisable(GL_CULL_FACE)));

            glm::mat4 P = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
            glm::mat4 V = glm::lookAt(
                glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

            _VP = P * V;
        }

        _program->attach(VertexShader(Shaders::vertexShader));
        _program->attach(FragmentShader(Shaders::fragmentShader));

        if (!_program->link())
        {
            Logger::out << "Error linking program" << std::endl;
            _context->window->close();
            return;
        }

        _resourceContainer.load<ColorTexture2D>("myTexture", "texture.png");

        static unsigned short indices[] =
        {
            0, 1, 2,
            0, 2, 3,
        };

        static double vertices[] =
        {
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,
            -1.0, 1.0, 0.0,
        };

        static float uvs[] =
        {
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,
        };

        _mesh = new Mesh();
        _mesh->setIndexBuffer(IndexBuffer(indices, 2, 3));
        _mesh->setVertexBuffer(ArrayBuffer(vertices, 4, 3));
        _mesh->setUVBuffer(ArrayBuffer(uvs, 4, 2));

        _material->diffuseMap = _resourceContainer.get<ColorTexture2D>("myTexture");

        _model->mesh = _mesh;
        _model->material = _material;

        _entity->setPosition(glm::vec3(0, -1, 0));
        _entity->model = _model;
    }

    DemoScene::~DemoScene()
    {
        delete _vertexArray;
        delete _program;
        delete _mesh;
        delete _material;
        delete _model;
        delete _entity;
    }

    void DemoScene::processWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                SceneEvent sceneEvent;
                sceneEvent.type = End;
                pushEvent(sceneEvent);
            }
        }
    }

    void DemoScene::processEngineEvent(const EngineEvent& event)
    {
    }

    void DemoScene::update(const double deltaTime)
    {
        _entity->setPosition(_entity->getPosition() + glm::vec3(0, 0.2 * deltaTime, 0));
        _entity->setRotation(_entity->getRotation() + glm::vec3(0.4 * deltaTime, 0.8 * deltaTime, 1.6 * deltaTime));
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BIND(Program, _program);
        {
            _program->setUniform("MVP", _VP * _entity->getModelMatrix());

            BIND(Texture, _entity->model->material->diffuseMap, 0);
            {
                _vertexArray->attachMesh(_entity->model->mesh);
                _vertexArray->render();
            }
            UNBIND(Texture, 0);
        }
        UNBIND(Program);
    }
}
