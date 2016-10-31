#pragma once

#include "../../../ImasiEngine/Source/Engine/Scene.hpp"
#include "../../../ImasiEngine/Source/Graphics/Shaders/Shader.hpp"
#include "../../../ImasiEngine/Source/Graphics/Buffers/VertexArray.hpp"
#include "../Game/GameContext.hpp"

namespace Imasi
{
    class DemoScene : public ImasiEngine::Scene
    {
    private:

        ImasiEngine::Shader* _shader;
        ImasiEngine::VertexArray* _vertexArray;

        GameContext* getContext() const;

    public:

        DemoScene();
        ~DemoScene();

        void processWindowEvent(const sf::Event& event) override;

        void update(const double deltaTime) override;
        void render() override;
    };
}
