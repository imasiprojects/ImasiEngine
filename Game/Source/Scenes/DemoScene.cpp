#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/DeleteMe/MeshLoader.hpp"
#include "../Resources/ResourceCodes.hpp"

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context)
        : Scene()
        , _context(context)
        , _camera(Camera())
        , _renderer(new InstancedRenderer(2500))
    {
        int mapSize = 11;

        _camera.setAspectRatio(_context->window->getSize().x / (float)_context->window->getSize().y);
        _camera.setPosition({ mapSize * -0.65f, 3.f, 3.f });
        _camera.lookAt({ mapSize * -0.65f, 0.f, -3.f });

        ColorTexture2D texture;
        texture.loadFromFile("Resources/katarina_diffuse.png");
        _resourceContainer.set(ResourceCodes::myTexture, std::move(texture));

        _resourceContainer.set(ResourceCodes::myMesh, std::move(*loadMesh("Resources/katarina.fbx")));

        Material myMaterial;
        myMaterial.diffuseMap = _resourceContainer.getColorTexture(ResourceCodes::myTexture);
        _resourceContainer.set(ResourceCodes::myMaterial, std::move(myMaterial));

        Model myModel;
        myModel.mesh = _resourceContainer.getMesh(ResourceCodes::myMesh);
        myModel.material = _resourceContainer.getMaterial(ResourceCodes::myMaterial);
        _resourceContainer.set(ResourceCodes::myModel, std::move(myModel));

        for (int i = 0; i < mapSize; i++)
        {
            for (int j = 0; j < mapSize; j++)
            {
                Entity* entity = new Entity();
                entity->model = _resourceContainer.getModel(ResourceCodes::myModel);
                entity->setPosition({ -i * 1.25f, 0, -j * 1.25f });
                entity->setScale(glm::vec3(0.25f));

                _entities.push_back(entity);
            }
        }

        sf::Vector2i centerWindow = sf::Vector2i(_context->window->getSize().x / 2, _context->window->getSize().y / 2);
        sf::Mouse::setPosition(centerWindow, *_context->window);
        _inputHandler.resetMouseMovement(centerWindow);
    }

    DemoScene::~DemoScene()
    {
        delete _renderer;

        for (auto& entity : _entities)
        {
            delete entity;
        }
    }

    void DemoScene::processWindowEvent(const sf::Event& event)
    {
        _inputHandler.processWindowEvent(event);

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

        // ROTATING KATARINA
        static bool change = false;
        static glm::vec3 rotation;
        bool next = change;

        for (Entity* entity : _entities)
        {
            if (next)
            {
                entity->setRotation(rotation);
            }

            next = !next;
        }

        rotation += glm::vec3(0, 2 * deltaTime, 0);

        if (rotation.y >= 2 * 3.14159)
        {
            rotation.y = 0;
            change = !change;
        }

        // JUMPING KATARINA
        static Entity* kata1;
        static Entity* kata2;
        static glm::vec3 kata1Initial;
        static glm::vec3 kata2Initial;
        static float maxTime = 0;
        static float actualTime = 0;

        if (actualTime >= maxTime)
        {
            kata1 = *std::next(_entities.begin(), rand() % _entities.size());
            kata2 = *std::next(_entities.begin(), rand() % _entities.size());

            kata1Initial = kata1->getPosition();
            kata2Initial = kata2->getPosition();

            maxTime = 1.f;
            actualTime = 0;
        }

        if (maxTime > 0)
        {
            actualTime += deltaTime;

            kata1->setPosition(glm::vec3(
                kata1Initial.x + (kata2Initial.x - kata1Initial.x) * actualTime / maxTime,
                kata1Initial.y + 2 * sin(actualTime / maxTime * 3.14159),
                kata1Initial.z + (kata2Initial.z - kata1Initial.z) * actualTime / maxTime
            ));

            kata2->setPosition(glm::vec3(
                kata2Initial.x + (kata1Initial.x - kata2Initial.x) * actualTime / maxTime,
                kata2Initial.y + 2 * sin(actualTime / maxTime * 3.14159),
                kata2Initial.z + (kata1Initial.z - kata2Initial.z) * actualTime / maxTime
            ));
        }
    }

    void DemoScene::updateFromInput(const float deltaTime)
    {
        if (_inputHandler.isMouseButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mouseMovement = _inputHandler.getMouseMovement();

            if (mouseMovement.x != 0 || mouseMovement.y != 0)
            {
                _camera.addRotationOffset(glm::vec2(mouseMovement.x, mouseMovement.y) * 0.15f);

                sf::Vector2i centerWindow = sf::Vector2i(_context->window->getSize().x / 2, _context->window->getSize().y / 2);
                sf::Mouse::setPosition(centerWindow, *_context->window);

                _inputHandler.resetMouseMovement(centerWindow);
            }
        }

        float speed = 10.f * deltaTime;

        glm::vec3 cameraMovementDirection = glm::vec3(0.f, 0.f, 0.f);
        
        if (_inputHandler.isKeyPressed(sf::Keyboard::W))
        {
            cameraMovementDirection += _camera.getForwardVector();
        }

        if (_inputHandler.isKeyPressed(sf::Keyboard::S))
        {
            cameraMovementDirection += _camera.getBackwardVector();
        }

        if (_inputHandler.isKeyPressed(sf::Keyboard::D))
        {
            cameraMovementDirection += _camera.getRightVector();
        }

        if (_inputHandler.isKeyPressed(sf::Keyboard::A))
        {
            cameraMovementDirection += _camera.getLeftVector();
        }

        if (_inputHandler.isKeyPressed(sf::Keyboard::Space))
        {
            cameraMovementDirection += glm::vec3(0.f, 1.f, 0.f);
        }

        if (_inputHandler.isKeyPressed(sf::Keyboard::LShift))
        {
            cameraMovementDirection += glm::vec3(0.f, -1.f, 0.f);
        }

        if (cameraMovementDirection != glm::vec3(0.f, 0.f, 0.f))
        {
            cameraMovementDirection = glm::normalize(cameraMovementDirection);
            _camera.addPositionOffset(cameraMovementDirection * speed);
        }
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _renderer->clear();
        _renderer->add(_entities.begin(), _entities.size());
        _renderer->render(_camera);
    }
}
