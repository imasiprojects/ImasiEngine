#ifndef IMASIENGINE_RENDERER_HPP
#define IMASIENGINE_RENDERER_HPP

#include <glm/glm.hpp>
#include <list>
#include "../Entity.hpp"

namespace ImasiEngine
{
    class Renderer
    {
    protected:

        std::list<Entity*> _entities;

        Renderer();
        virtual ~Renderer();

    public:

        virtual void clear();
        virtual void addEntity(Entity* entity);
        virtual void render(glm::mat4& VP) const = 0;
    };
}

#endif
