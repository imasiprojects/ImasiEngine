#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Utils/Logger.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/FragmentShader.hpp"
#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Utils/Opengl.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context) : Scene()
    {
        _context = context;

        _program = new Program();

        // Example with pointers
        VertexShader vertexShader;
        vertexShader.compile(Shaders::vertexShader);
        _program->attach(vertexShader);

        // Example without pointers
        _program->attach(FragmentShader(Shaders::fragmentShader));

        if (!_program->link())
        {
            Logger::out << "Error linking program" << std::endl;
            _context->window->close();
            return;
        }

        _texture = new ColorTexture2D();
        if (!_texture->loadFromFile("texture.png"))
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

        _vertexArray = new VertexArray();
        _vertexArray->attachMesh(_mesh);
    }

    DemoScene::~DemoScene()
    {
        delete _mesh;
        delete _vertexArray;
        delete _program;
        delete _texture;
    }

    void DemoScene::processWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _context->window->close();
            }
        }
    }

    void DemoScene::update(const double deltaTime)
    {
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        USING(_program,
        {
            USING(_texture,
            {
                _vertexArray->render();
            });
        });
    }
}
