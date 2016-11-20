#ifndef IMASIENGINE_RENDERER_HPP
#define IMASIENGINE_RENDERER_HPP

#include <set>

#include "../Entity.hpp"
#include "../Cameras/Camera.hpp"

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
        virtual void render(glm::mat4& vp) const = 0;
    };
}

#endif
