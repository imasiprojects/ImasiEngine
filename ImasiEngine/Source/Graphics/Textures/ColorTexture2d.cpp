#include "ColorTexture2d.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    ColorTexture2d::ColorTexture2d() : Texture(),
        _width(0),
        _height(0)
    {
        _type = GL_TEXTURE_2D;
    }

    ColorTexture2d::~ColorTexture2d()
    {
        
    }

    unsigned int ColorTexture2d::getWidth() const
    {
        return _width;
    }

    unsigned ColorTexture2d::getHeight() const
    {
        return _height;
    }

    void ColorTexture2d::create(unsigned int width, unsigned int height)
    {
        GL(glGenTextures(1, &_id));

        Texture::bind(this);

        GL(glTexImage2D(_type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));

        GL(glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL(glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

        Texture::unbind();

        _width = width;
        _height = height;
    }

    bool ColorTexture2d::loadFromFile(const char* fileName)
    {
        sf::Image image;
        if (!image.loadFromFile(fileName))
        {
            return false;
        }

        sf::Vector2u imageSize = image.getSize();

        GL(glGenTextures(1, &_id));

        Texture::bind(this);

        GL(glTexImage2D(_type, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
        GL(glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL(glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL(glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL(glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        GL(glGenerateMipmap(_type));

        Texture::unbind();

        _width = imageSize.x;
        _height = imageSize.y;

        return true;
    }

}
