#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Utils/Logger.hpp"
#include "../../../ImasiEngine/Source/Utils/Opengl.hpp"
#include "../../../ImasiEngine/Source/DeleteMe/MeshLoader.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context)
        : Scene()
        , _context(context)
        , _camera(Camera())
        , _renderer(new Simple3DRenderer())
        , _entity(new Entity())
    {
        GL(glDisable(GL_CULL_FACE));

        _camera.setViewportAspectRatio(_context->window->getSize().x / _context->window->getSize().y);
        _camera.setPosition(glm::vec3(0, 1, 3));
        _camera.lookAt(glm::vec3(0, 0, 0));

        ColorTexture2D texture;
        texture.loadFromFile("Resources/texture.png");
         _resourceContainer.set("myTexture", std::move(texture));

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

        Mesh myMesh;
        myMesh.setIndexBuffer(IndexBuffer(indices, 2, 3));
        myMesh.setVertexBuffer(ArrayBuffer(vertices, 4, 3));
        myMesh.setUVBuffer(ArrayBuffer(uvs, 4, 2));
        _resourceContainer.set("myMesh", std::move(myMesh));

        Material myMaterial;
        myMaterial.diffuseMap = _resourceContainer.getColorTexture("myTexture");
        _resourceContainer.set("myMaterial", std::move(myMaterial));

        Model myModel;
        myModel.mesh = _resourceContainer.getMesh("myMesh");
        myModel.material = _resourceContainer.getMaterial("myMaterial");
        _resourceContainer.set("myModel", std::move(myModel));

        _entity->setPosition(glm::vec3(0, 0, 0));
        _entity->model = _resourceContainer.getModel("myModel");
    }

    DemoScene::~DemoScene()
    {
        delete _renderer;
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

            if (event.key.code == sf::Keyboard::G)
            {
                _camera.lookAt(glm::vec3(0, 0, 0));
            }
        }
    }

    void DemoScene::processEngineEvent(const EngineEvent& event)
    {
    }

    void DemoScene::update(const double deltaTime)
    {
        static unsigned int fps;
        static double elapsedTime;

        fps++;
        elapsedTime += deltaTime;

        if (elapsedTime >= 1.0)
        {
            _context->window->setTitle("Fps: " + std::to_string(fps));
            fps = 0;
            elapsedTime -= 1.0;
        }

        if (_context->window->hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float sensibilidad = -0.15f;

            sf::Vector2i centerWindow = sf::Vector2i(_context->window->getSize().x / 2, _context->window->getSize().y / 2);
            sf::Vector2i diferencia = centerWindow - sf::Mouse::getPosition(*_context->window);
            if (diferencia.x != 0 || diferencia.y != 0)
            {
                _camera.offsetOrientation(diferencia.y * sensibilidad, diferencia.x * sensibilidad);
                sf::Mouse::setPosition(centerWindow, *_context->window);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _camera.offsetPosition(_camera.forward() * (float)(2.f * deltaTime));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _camera.offsetPosition(_camera.forward() * (float)(-2.f * deltaTime));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _camera.offsetPosition(_camera.right() * (float)(2.f * deltaTime));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _camera.offsetPosition(_camera.right() * (float)(-2.f * deltaTime));
        }
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _renderer->clear();
        _renderer->addEntity(_entity);
        _renderer->render(_camera.matrix());
    }
}
