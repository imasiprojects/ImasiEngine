#pragma once

#include "Texture.hpp"

namespace ImasiEngine
{
    class ColorTexture2d : public Texture
    {
    private:

        unsigned int _width, _height;

    public:

        unsigned int getWidth() const;
        unsigned int getHeight() const;

        ColorTexture2d();
        ~ColorTexture2d();

        void create(unsigned int width, unsigned int height);
        bool loadFromFile(const char* fileName);
    };
}