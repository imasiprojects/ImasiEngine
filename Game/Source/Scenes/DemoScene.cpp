#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Graphics/Shaders/Shader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/Buffer.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/VertexArray.hpp"
#include "../../../ImasiEngine/Source/Utils/Logger.hpp"

#include "../Shaders/FragmentShader.hpp"
#include "../Shaders/VertexShader.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene() : Scene()
    {
        _shader = new Shader();
        _shader->loadFromStrings(Shaders::vertexShader, Shaders::fragmentShader);

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
        delete _shader;
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
    }
    
    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader::bind(_shader);
        VertexArray::bind(_vertexArray);
        VertexArray::draw(_vertexArray);
        VertexArray::unbind();
        Shader::unbind();
    }
}
