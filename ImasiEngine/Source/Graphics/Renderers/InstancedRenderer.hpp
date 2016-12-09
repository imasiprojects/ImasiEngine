#ifndef IMASIENGINE_INSTANCEDRENDERER_HPP
#define IMASIENGINE_INSTANCEDRENDERER_HPP

#include <list>
#include <mutex>

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

        Program* _program;
        VertexArray* _vertexArray;

        const unsigned int _maxVectorSize;

        std::list<std::vector<Entity*>> _entities;

        void optimizeEntities(const glm::mat4& VP, std::map<Model*, std::list<ArrayBuffer*> >& optimizedEntities) const;
        bool isVisible(const glm::mat4& MVP, const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f)) const;

    public:

        InstancedRenderer(unsigned int maxVectorSize = 10000);
        ~InstancedRenderer();

        void add(Entity* entity);

        template<typename InputIterator>
        void add(InputIterator entityIterator, size_t entityCount)
        {
            sf::Clock clock;

            size_t count = 0;

            while (count < entityCount)
            {
                if (_entities.size() == 0 || _entities.back().size() >= _entities.back().capacity())
                {
                    _entities.push_back(std::vector<Entity*>());
                    _entities.back().reserve(_maxVectorSize);
                }

                std::vector<Entity*>& v = _entities.back();
                unsigned int vectorSize = (unsigned int)v.size();

                if (entityCount - count >= v.capacity() - vectorSize)
                {
                    v.resize(v.capacity());
                    for (unsigned int i = vectorSize; i < v.capacity(); i++)
                    {
                        v[i] = *entityIterator++;
                    }
                    count += v.capacity() - vectorSize;
                }
                else
                {
                    v.resize(vectorSize + entityCount - count);
                    for (int i = vectorSize; i < entityCount - count; i++)
                    {
                        v[i] = *entityIterator++;
                    }
                    count = entityCount;
                }
            }

            std::cout << "Add entities: " << clock.restart().asMilliseconds() << std::endl;
        }

        void clear() override;
        void render(const glm::mat4& VP) override;
        void render(Camera& camera);
    };
}

#endif
