#include "Renderer.hpp"

namespace ImasiEngine
{
    Renderer::Renderer()
    {
        
    }

    Renderer::~Renderer()
    {
        
    }

    void Renderer::clear()
    {
        _entities.clear();
    }

    void Renderer::addEntity(Entity* entity)
    {
        _entities.push_back(entity);
    }
}
