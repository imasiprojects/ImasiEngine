#pragma once

#include "Texture.hpp"

namespace ImasiEngine
{
    class ColorTexture2D : public Texture
    {
    private:

        unsigned int _width, _height;

    public:

        unsigned int getWidth() const;
        unsigned int getHeight() const;

        ColorTexture2D();
        ColorTexture2D(const ColorTexture2D&) = delete;
        ColorTexture2D(ColorTexture2D&& texture) noexcept;
        virtual ~ColorTexture2D();

        unsigned int getTextureType() const override;

        void create(unsigned int width, unsigned int height);
        bool loadFromFile(const char* fileName);
    };
}