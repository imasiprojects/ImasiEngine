#ifndef IMASIENGINE_RENDERER_HPP
#define IMASIENGINE_RENDERER_HPP

#include <glm/glm.hpp>

#include "../Entities/Entity.hpp"
namespace ImasiEngine
{
    class Renderer
    {
    protected:

        Renderer();
        virtual ~Renderer();

    public:

        virtual void clear() = 0;
        virtual void render(glm::mat4& VP) = 0;
        virtual void render(const glm::mat4& VP) const = 0;
    };
}

#endif
