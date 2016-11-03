#include "Texture.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    std::map<unsigned int, unsigned int> Texture::_indexTypes;

    void Texture::bind(Texture* texture, unsigned int index)
    {
        unsigned int type = texture->getOpenglTextureType();

        _indexTypes[index] = type;

        GL(glActiveTexture(GL_TEXTURE0 + index));
        GL(glEnable(type));
        GL(glBindTexture(type, texture->getGLObjectId()));
    }

    void Texture::unbind(unsigned int index)
    {
        auto indexIterator = _indexTypes.find(index);

        if (indexIterator != _indexTypes.end())
        {
            unsigned int type = indexIterator->second;

            GL(glActiveTexture(GL_TEXTURE0 + index));
            GL(glBindTexture(type, NULL_ID));
            GL(glDisable(type));

            _indexTypes.erase(indexIterator);
        }
    }

    Texture::Texture()
        : GLObject()
    {
    }

    Texture::Texture(Texture&& texture) noexcept
        : GLObject(std::move(texture))
    {
    }

    Texture::~Texture()
    {
        if (Texture::isValidGLObject())
        {
            Texture::destroyGLObject();
        }
    }

    void Texture::createGLObject()
    {
        unsigned int id;
        GL(glGenTextures(1, &id));

        setGLObjectId(id);
    }

    void Texture::destroyGLObject()
    {
        unsigned int id = getGLObjectId();
        glDeleteTextures(1, &id);

        unsetGLObjectId();
    }
}
