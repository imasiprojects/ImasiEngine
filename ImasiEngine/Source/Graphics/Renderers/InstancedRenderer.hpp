#ifndef IMASIENGINE_INSTANCEDRENDERER_HPP
#define IMASIENGINE_INSTANCEDRENDERER_HPP

#include "Renderer.hpp"
#include "../Program.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Cameras/Camera.hpp"
#include "../Model.hpp"
#include <list>
#include "../Entity.hpp"

namespace ImasiEngine
{
    class InstancedRenderer
        : public Renderer
    {
    private:

        static const char* _fragmentShader;
        static const char* _vertexShader;
        static const unsigned int _maxVectorSize = 10000000; // Not working for multiple vectors

    protected:

        Program* _program;
        VertexArray* _vertexArray;

        std::list<std::vector<Entity*>> _entities;
        std::map<Model*, std::list<glm::mat4>> _optimizedEntities;
        void InstancedRenderer::prepareOptimizedEntities(glm::mat4& VP);
        bool isVisible(glm::mat4& MVP, glm::vec3& position = glm::vec3(0.f, 0.f, 0.f)) const;

    public:

        InstancedRenderer();
        ~InstancedRenderer();

        void add(const std::list<Entity*>& entities);

        void clear() override;
        void render(glm::mat4& VP) override;
        void render(Camera& camera);
    };
}

#endif
