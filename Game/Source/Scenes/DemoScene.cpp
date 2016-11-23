#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Utils/Logger.hpp"
#include "../../../ImasiEngine/Source/Utils/Opengl.hpp"
#include "../../../ImasiEngine/Source/DeleteMe/MeshLoader.hpp"
#include "../../Resources/ResourceCodes.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context, ServiceContainer& serviceContainer)
        : Scene()
        , _context(context)
        , _camera(Camera())
        , _renderer(new Simple3DRenderer())
        , _entity(new Entity())
    {
        _demoService = serviceContainer.get<DemoService>();

        GL(glDisable(GL_CULL_FACE));

        _camera.setAspectRatio(_context->window->getSize().x / (float)_context->window->getSize().y);
        _camera.setPosition(glm::vec3(4, 3, 3));
        _camera.lookAt(glm::vec3(0, 0, 0));

        ColorTexture2D texture;
        texture.loadFromFile("Resources/texture.png");
        _resourceContainer.set(ResourceCodes::myTexture, std::move(texture));

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
        _resourceContainer.set(ResourceCodes::myMesh, std::move(myMesh));

        Material myMaterial;
        myMaterial.diffuseMap = _resourceContainer.getColorTexture(ResourceCodes::myTexture);
        _resourceContainer.set(ResourceCodes::myMaterial, std::move(myMaterial));

        Model myModel;
        myModel.mesh = _resourceContainer.getMesh(ResourceCodes::myMesh);
        myModel.material = _resourceContainer.getMaterial(ResourceCodes::myMaterial);
        _resourceContainer.set(ResourceCodes::myModel, std::move(myModel));

        _entity->setPosition(glm::vec3(0, 0, 0));
        _entity->model = _resourceContainer.getModel(ResourceCodes::myModel);
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

            if (event.key.code == sf::Keyboard::K)
            {
                _demoService->increment();
                _context->window->setTitle(std::to_string(_demoService->getNumber()));
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

    void DemoScene::update(const float deltaTime)
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

        if (_context->window->hasFocus())
        {
            updateFromInput(deltaTime);
        }
    }

    void DemoScene::updateFromInput(const float deltaTime)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i centerWindow = sf::Vector2i(_context->window->getSize().x / 2, _context->window->getSize().y / 2);
            sf::Vector2i diferencia = centerWindow - sf::Mouse::getPosition(*_context->window);

            if (diferencia.x != 0 || diferencia.y != 0)
            {
                _camera.addRotationOffset(glm::vec2(diferencia.x, diferencia.y) * -0.15f);
                sf::Mouse::setPosition(centerWindow, *_context->window);
            }
        }

        float speed = 4.f * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            _camera.addPositionOffset(_camera.getForwardVector() * speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            _camera.addPositionOffset(_camera.getBackwardVector() * speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            _camera.addPositionOffset(_camera.getRightVector() * speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            _camera.addPositionOffset(_camera.getLeftVector() * speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _camera.addPositionOffset(glm::vec3(0.f, 1.f, 0.f) * speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            _camera.addPositionOffset(glm::vec3(0.f, -1.f, 0.f) * speed);
        }
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _renderer->clear();
        _renderer->addEntity(_entity);
        _renderer->render(_camera);
    }
}
