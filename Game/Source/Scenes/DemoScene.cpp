#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Utils/Logger.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/FragmentShader.hpp"
#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Utils/Opengl.hpp"
#include "../../../ImasiEngine/Source/DeleteMe/MeshLoader.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context)
        : Scene()
        , _context(context)
        , _vertexArray(new VertexArray())
        , _program(new Program())
        , _texture(new ColorTexture2D())
        , _material(new Material())
        , _model(new Model())
    {
        _program->attach(VertexShader(Shaders::vertexShader));
        _program->attach(FragmentShader(Shaders::fragmentShader));

        if (!_program->link())
        {
            Logger::out << "Error linking program" << std::endl;
            _context->window->close();
            return;
        }

        if (!_texture->loadFromFile("Resources/texture.png"))
        {
            Logger::out << "Error loading Texture" << std::endl;
        }

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

        _material->diffuseMap = _texture;

        _model->mesh = _mesh;
        _model->material = _material;
    }

    DemoScene::~DemoScene()
    {
        delete _vertexArray;
        delete _program;
        delete _mesh;
        delete _texture;
        delete _material;
        delete _model;
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
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BIND(Program, _program);
        {
            BIND(Texture, _model->material->diffuseMap, 0);
            {
                _vertexArray->attachMesh(_model->mesh);
                _vertexArray->render();
            }
            UNBIND(Texture, 0);
        }
        UNBIND(Program);
    }
}
