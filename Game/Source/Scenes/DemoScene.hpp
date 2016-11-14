#ifndef IMASIGAME_DEMOSCENE_HPP
#define IMASIGAME_DEMOSCENE_HPP

#include "../../../ImasiEngine/Source/Engine/Scene.hpp"
#include "../../../ImasiEngine/Source/Graphics/Mesh.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/VertexArray.hpp"
#include "../../../ImasiEngine/Source/Graphics/Program.hpp"
#include "../../../ImasiEngine/Source/Graphics/Textures/ColorTexture2D.hpp"
#include "../../../ImasiEngine/Source/Graphics/Model.hpp"
#include "../../../ImasiEngine/Source/Graphics/Entity.hpp"
#include "../Game/GameContext.hpp"

namespace Imasi
{
    class DemoScene : public ImasiEngine::Scene
    {
    private:

        GameContext* _context;

        glm::mat4 _VP;

        ImasiEngine::VertexArray* _vertexArray;
        ImasiEngine::Program* _program;
        ImasiEngine::Mesh* _mesh;
        ImasiEngine::ColorTexture2D* _texture;
        ImasiEngine::Material* _material;
        ImasiEngine::Model* _model;
        ImasiEngine::Entity* _entity;

    public:

        DemoScene(GameContext* context);
        ~DemoScene();

        void processWindowEvent(const sf::Event& event) override;
        void processEngineEvent(const ImasiEngine::EngineEvent& event) override;

        void update(const double deltaTime) override;
        void render() override;
    };
}

#endif
