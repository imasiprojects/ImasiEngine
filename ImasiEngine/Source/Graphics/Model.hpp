#ifndef IMASIENGINE_MODEL_HPP
#define IMASIENGINE_MODEL_HPP

#include "Mesh.hpp"
#include "Material.hpp"

namespace ImasiEngine
{
    class Model
    {
    private:

        Mesh* _mesh;
        Material* _material;

    public:

        Model()
            : _mesh(nullptr)
            , _material(nullptr)
        {
        }

        Mesh* getMesh() const
        {
            return _mesh;
        }

        void setMesh(Mesh* mesh)
        {
            _mesh = mesh;
        }

        Material* getMaterial() const
        {
            return _material;
        }

        void setMaterial(Material* material)
        {
            _material = material;
        }
    };
}

#endif
