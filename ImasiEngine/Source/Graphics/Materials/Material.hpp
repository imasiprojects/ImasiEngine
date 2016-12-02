#ifndef IMASIENGINE_MATERIAL_HPP
#define IMASIENGINE_MATERIAL_HPP

#include "../Textures/ColorTexture2D.hpp"

namespace ImasiEngine
{
    struct Material
    {
        ColorTexture2D* diffuseMap;

        Material()
            : diffuseMap(nullptr)
        {
        }
    };
}

#endif
