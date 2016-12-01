#ifndef IMASIENGINE_INSTANCEDRENDERER_HPP
#define IMASIENGINE_INSTANCEDRENDERER_HPP

#include <list>
#include <mutex>

#include "Renderer.hpp"
#include "../Program.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Cameras/Camera.hpp"
#include "../Model.hpp"
#include "../Entity.hpp"

namespace ImasiEngine
{
    class InstancedRenderer
        : public Renderer
    {
    private:

        static const char* _fragmentShader;
        static const char* _vertexShader;

    protected:

        Program* _program;
        VertexArray* _vertexArray;

        const unsigned int _maxVectorSize;

        std::list<std::vector<Entity*>> _entities;
        std::map<Model*, std::list<glm::mat4>> _optimizedEntities;
        std::mutex _optimizedEntitiesMutex;

        void InstancedRenderer::prepareOptimizedEntities(glm::mat4& VP);
        bool isVisible(glm::mat4& MVP, glm::vec3& position = glm::vec3(0.f, 0.f, 0.f)) const;

    public:

        InstancedRenderer(unsigned int maxVectorSize = 10000);
        ~InstancedRenderer();

        void add(Entity* entity);
        void add(const std::list<Entity*>& entities);

        void clear() override;
        void render(glm::mat4& VP) override;
        void render(Camera& camera);
    };
}

#endif
