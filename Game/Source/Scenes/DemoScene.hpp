#ifndef IMASIGAME_DEMOSCENE_HPP
#define IMASIGAME_DEMOSCENE_HPP

#include "../../../ImasiEngine/Source/Engine/Scene.hpp"
#include "../../../ImasiEngine/Source/Graphics/Entity.hpp"
#include "../../../ImasiEngine/Source/Graphics/Renderers/Simple3DRenderer.hpp"
#include "../../../ImasiEngine/Source/Resources/ResourceContainer.hpp"
#include "../Game/GameContext.hpp"

namespace Imasi
{
    class DemoScene : public ImasiEngine::Scene
    {
    private:

        GameContext* _context;

        glm::mat4 _VP;
        
        ImasiEngine::Simple3DRenderer* _renderer;
        ImasiEngine::ResourceContainer<> _resourceContainer;
        ImasiEngine::Entity* _entity;

    public:

        DemoScene(GameContext* context);
        ~DemoScene();

        void processWindowEvent(const sf::Event& event) override;
        void processEngineEvent(const ImasiEngine::EngineEvent& event) override;

        void update(const float deltaTime) override;
        void render() override;
    };
}

#endif
