#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Graphics/Buffers/Buffer.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/VertexArray.hpp"
#include "../../../ImasiEngine/Source/Utils/Logger.hpp"

#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/VertexShader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/FragmentShader.h"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context) : Scene()
    {
        _context = context;

        _program = new Program();

        // Example with pointers
        VertexShader* vertexShader = new VertexShader();
        vertexShader->load(Shaders::vertexShader);
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

        _vertexArray = new VertexArray();
        _vertexArray->addBuffer(new Buffer(vertices, 3, 3), Vertex);
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
        Logger::out << "DeltaTime: " << deltaTime << "s" << std::endl;
        Logger::out << "Context: " << _context->level << std::endl;
    }
    
    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Program::bind(_program);
        _vertexArray->draw();
        Program::unbind();
    }
}
