#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Graphics/Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/FragmentShader.hpp"
#include "../../../ImasiEngine/Source/Utils/Logger.hpp"

#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"

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

        static float vertices[] =
        {
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f,
        };

        static float uvs[] =
        {
            0.f, 1.f,
            1.f, 1.f,
            0.5f, 0.f
        };

        _vertexBuffer = new Buffer(vertices, 3, 3);
        _UVBuffer = new Buffer(uvs, 3, 2);

        _vertexArray = new VertexArray();
        _vertexArray->attachBuffer(_vertexBuffer, Vertex);
        _vertexArray->attachBuffer(_UVBuffer, UV);
    }

    DemoScene::~DemoScene()
    {
        delete _program;
        delete _vertexBuffer;
        delete _UVBuffer;
        delete _vertexArray;
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

        Program::bind(_program);
        {
            Texture::bind(_texture);
            {
                _vertexArray->draw();
            }
            Texture::unbind();
        }
        Program::unbind();
    }
}
