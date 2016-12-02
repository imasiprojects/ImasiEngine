#ifndef IMASIENGINE_RENDERER_HPP
#define IMASIENGINE_RENDERER_HPP

#include <set>

#include <glm/glm.hpp>

#include "../Entities/Entity.hpp"

namespace ImasiEngine
{
    class Renderer
    {
    protected:

        std::set<Entity*> _entities;

        Renderer();
        virtual ~Renderer();

    public:

        virtual void clear();
        virtual void addEntity(Entity* entity);
        virtual void render(glm::mat4& VP) const = 0;
    };
}

#endif
