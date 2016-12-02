#ifndef IMASIGAME_DEMOSCENE_HPP
#define IMASIGAME_DEMOSCENE_HPP

#include "../../../ImasiEngine/Source/Engine/Scene.hpp"
#include "../../../ImasiEngine/Source/Graphics/Entities/Entity.hpp"
#include "../../../ImasiEngine/Source/Graphics/Renderers/Simple3DRenderer.hpp"
#include "../../../ImasiEngine/Source/Resources/ResourceContainer.hpp"
#include "../../../ImasiEngine/Source/Graphics/Cameras/Camera.hpp"
#include "../Game/GameContext.hpp"
#include "../Engine/InputHandler.hpp"

namespace Imasi
{
    class DemoScene : public ImasiEngine::Scene
    {
    private:

        GameContext* _context;
        InputHandler _inputHandler;

        ImasiEngine::Camera _camera;
        
        ImasiEngine::Simple3DRenderer* _renderer;
        ImasiEngine::ResourceContainer<> _resourceContainer;
        ImasiEngine::Entity* _entity;

    public:

        DemoScene(GameContext* context);
        ~DemoScene();

        void processWindowEvent(const sf::Event& event) override;
        void processEngineEvent(const ImasiEngine::EngineEvent& event) override;

        void update(const float deltaTime) override;
        void updateFromInput(const float deltaTime);
        void render() override;
    };
}

#endif
