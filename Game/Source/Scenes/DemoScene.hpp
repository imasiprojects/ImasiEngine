#pragma once

#include "../../../ImasiEngine/Source/Engine/Scene.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/VertexArray.hpp"
#include "../Game/GameContext.hpp"
#include "../../../ImasiEngine/Source/Graphics/Program.hpp"

namespace Imasi
{
    class DemoScene : public ImasiEngine::Scene
    {
    private:

        GameContext* _context;

        ImasiEngine::Program* _program;
        ImasiEngine::VertexArray* _vertexArray;

    public:

        DemoScene(GameContext* context);
        ~DemoScene();

        void processWindowEvent(const sf::Event& event) override;

        void update(const double deltaTime) override;
        void render() override;
    };
}
