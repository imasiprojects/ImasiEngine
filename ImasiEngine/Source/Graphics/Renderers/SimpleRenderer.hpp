#ifndef IMASIENGINE_SIMPLERENDERER_HPP
#define IMASIENGINE_SIMPLERENDERER_HPP

#include "Renderer.hpp"
#include "../Program.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Cameras/Camera.hpp"
#include <list>
#include "../Entity.hpp"

namespace ImasiEngine
{
    class SimpleRenderer
        : public Renderer
    {
    private:

        static const char* _fragmentShader;
        static const char* _vertexShader;

    protected:
        
        std::list<Entity*> _entities;

        Program* _program;
        VertexArray* _vertexArray;

    public:

        SimpleRenderer();
        ~SimpleRenderer();

        void clear() override;
        void add(Entity* entity);
        void add(std::list<Entity*>& entities);

        void render(glm::mat4& VP) override;
        void render(Camera& camera);
    };
}

#endif
