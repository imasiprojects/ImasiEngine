#ifndef IMASIENGINE_RENDERER_HPP
#define IMASIENGINE_RENDERER_HPP

#include <glm/glm.hpp>

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
    };
}

#endif
