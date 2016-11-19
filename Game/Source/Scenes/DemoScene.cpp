#include "DemoScene.hpp"

#include <GL/glew.h>

#include "../../../ImasiEngine/Source/Utils/Logger.hpp"
#include "../../../ImasiEngine/Source/Utils/Opengl.hpp"
#include "../../../ImasiEngine/Source/DeleteMe/MeshLoader.hpp"
#include "../../Resources/ResourceCodes.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace ImasiEngine;

namespace Imasi
{
    DemoScene::DemoScene(GameContext* context)
        : Scene()
        , _context(context)
        , _renderer(new Simple3DRenderer())
        , _entity(new Entity())
    {
        // TEST
        {
            GL(glDisable(GL_CULL_FACE));

            glm::mat4 P = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
            glm::mat4 V = glm::lookAt(
                glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

            _VP = P * V;
        }

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

        _entity->setPosition(glm::vec3(0, -1, 0));
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

        _entity->setPosition(_entity->getPosition() + glm::vec3(0, 0.2 * deltaTime, 0));
        _entity->setRotation(_entity->getRotation() + glm::vec3(0.4 * deltaTime, 0.8 * deltaTime, 1.6 * deltaTime));
    }

    void DemoScene::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _renderer->clear();
        _renderer->addEntity(_entity);
        _renderer->render(_VP);
    }
}
