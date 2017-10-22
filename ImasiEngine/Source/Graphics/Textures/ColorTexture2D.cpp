#include "ColorTexture2D.hpp"

#include <GL/glew.h>

#include "../Opengl/OpenglHelper.hpp"

namespace ImasiEngine
{
    ColorTexture2D::ColorTexture2D()
        : Texture()
        , _width(0)
        , _height(0)
    {
    }

    ColorTexture2D::ColorTexture2D(ColorTexture2D&& texture) noexcept
        : Texture(std::move(texture))
        , _width(texture._width)
        , _height(texture._height)
    {
    }

    ColorTexture2D::~ColorTexture2D()
    {
    }

    GLEnums::TextureType ColorTexture2D::getGLTextureType() const
    {
        return GLEnums::TextureType::Texture2D;
    }

    unsigned int ColorTexture2D::getWidth() const
    {
        return _width;
    }

    unsigned ColorTexture2D::getHeight() const
    {
        return _height;
    }

    void ColorTexture2D::create(unsigned int width, unsigned int height)
    {
        unsigned int type = getGLTextureType();

        createGLObject();

        {
            auto textureBindGuard = OpenglHelper::makeBindGuard(*this, 0);

            GL(glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
            GL(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
            GL(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        }

        _width = width;
        _height = height;
    }

    bool ColorTexture2D::loadFromFile(const std::string& fileName)
    {
        sf::Image image;
        if (!image.loadFromFile(fileName))
        {
            return false;
        }

        sf::Vector2u imageSize = image.getSize();

        unsigned int type = getGLTextureType();

        createGLObject();

        {
            auto textureBindGuard = OpenglHelper::makeBindGuard(*this, 0);

            GL(glTexImage2D(type, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()));
            GL(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GL(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT));
            GL(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            GL(glGenerateMipmap(type));
        }

        _width = imageSize.x;
        _height = imageSize.y;

        return true;
    }

}
