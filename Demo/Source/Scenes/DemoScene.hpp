#ifndef IMASIGAME_DEMOSCENE_HPP
#define IMASIGAME_DEMOSCENE_HPP

#include <list>

#include "../../../ImasiEngine/Source/Engine/Scene.hpp"
#include "../../../ImasiEngine/Source/Graphics/Entities/Entity.hpp"
#include "../../../ImasiEngine/Source/Graphics/Renderers/InstancedRenderer.hpp"
#include "../../../ImasiEngine/Source/Resources/ResourceContainer.hpp"
#include "../../../ImasiEngine/Source/Graphics/Cameras/Camera.hpp"
#include "../../../ImasiEngine/Source/Experimental/InputHandler.hpp"

namespace Imasi
{
    class DemoScene : public ImasiEngine::Scene
    {
    private:

        ImasiEngine::Window* _window;
        ImasiEngine::InputHandler _inputHandler;

        ImasiEngine::Camera _camera;
        
        ImasiEngine::InstancedRenderer* _renderer;
        ImasiEngine::ResourceContainer<> _resourceContainer;
        std::list<ImasiEngine::Entity*> _entities;

        void onWindowResized();

    public:

        DemoScene();
        ~DemoScene();

        void processWindowEvent(const sf::Event& event) override;
        void processEngineEvent(const ImasiEngine::EngineEvent& event) override;

        void update(const float deltaTime) override;
        void updateFromInput(const float deltaTime);
        void render(sf::RenderTarget& renderTarget) override;
    };
}

#endif
