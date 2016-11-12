#ifndef IMASIENGINE_MODEL_HPP
#define IMASIENGINE_MODEL_HPP

#include "Mesh.hpp"
#include "Material.hpp"

namespace ImasiEngine
{
    struct Model
    {
        Mesh* mesh;
        Material* material;

        Model()
            : mesh(nullptr)
            , material(nullptr)
        {
        }
    };
}

#endif
