#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Graphics/Buffers/Buffer.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/VertexArray.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/FragmentShader.hpp"
#include "../../../ImasiEngine/Source/Utils/Logger.hpp"

#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Textures/ColorTexture2D.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context) : Scene()
    {
        _context = context;

        _program = new Program();

        // Example with pointers
        VertexShader* vertexShader = new VertexShader();
        vertexShader->compile(Shaders::vertexShader);
        _program->attach(*vertexShader);

        // Example without pointers
        _program->attach(FragmentShader(Shaders::fragmentShader));

        if(!_program->link())
        {
            Logger::out << "Error linking program" << std::endl;
        }

        static float vertices[] =
        {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
        };

        static float uvs[] =
        {
            0.f, 0.f,
            1.f, 1.f,
            0.5f, 0.5f
        };

        _vertexArray = new VertexArray();
        _vertexArray->addBuffer(new Buffer(vertices, 3, 3), Vertex);
        _vertexArray->addBuffer(new Buffer(uvs, 3, 2), UV);
    }

    DemoScene::~DemoScene()
    {
        delete _program;
        delete _vertexArray;
    }

    void DemoScene::processWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            Logger::out << "Key Pressed!" << std::endl;
        }
    }

    void DemoScene::update(const double deltaTime)
    {
    }
    
    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ColorTexture2D myTexture;
        myTexture.loadFromFile("texture.png");

        Program::bind(_program);
        _vertexArray->draw();
        Program::unbind();
    }
}
