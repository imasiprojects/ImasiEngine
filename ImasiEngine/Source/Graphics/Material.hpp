#ifndef IMASIENGINE_MATERIAL_HPP
#define IMASIENGINE_MATERIAL_HPP

#include "Textures/ColorTexture2D.hpp"

namespace ImasiEngine
{
    class Material
    {
    private:

        ColorTexture2D* _diffuseMap;

    public:

        Material()
            : _diffuseMap(nullptr)
        {
        }

        ColorTexture2D* getDiffuseMap() const
        {
            return _diffuseMap;
        }

        void setDiffuseMap(ColorTexture2D* diffuseMap)
        {
            _diffuseMap = diffuseMap;
        }
    };
}

#endif
