#ifndef IMASIENGINE_INSTANCEDRENDERER_HPP
#define IMASIENGINE_INSTANCEDRENDERER_HPP

#include <list>

#include "Renderer.hpp"
#include "../Programs/Program.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Cameras/Camera.hpp"
#include "../Models/Model.hpp"
#include "../Entities/Entity.hpp"

namespace ImasiEngine
{
    class InstancedRenderer
        : public Renderer
    {
    private:

        static const char* _fragmentShader;
        static const char* _vertexShader;

    protected:

        std::unique_ptr<Program> _program;
        std::unique_ptr<VertexArray> _vertexArray;

        const unsigned int _maxVectorSize;

        std::list<std::vector<Entity*>> _entities;

        void optimizeEntities(const glm::mat4& VP, std::map<Model*, std::unique_ptr<ArrayBuffer>>& optimizedEntities) const;
        bool isVisible(const glm::mat4& MVP, const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f)) const;

    public:

        InstancedRenderer(unsigned int maxVectorSize = 10000);

        void add(Entity* entity);
        void clear() override;
        void render(const glm::mat4& VP) override;
        void render(Camera& camera);
    };
}

#endif
