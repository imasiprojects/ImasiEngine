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
        GL(glBindTexture(type, texture->getGpuObjectId()));
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
        : GpuObject()
    {
    }

    Texture::Texture(Texture&& texture) noexcept
        : GpuObject(std::move(texture))
    {
    }

    Texture::~Texture()
    {
        if (Texture::isValidGpuObject())
        {
            Texture::destroyGpuObject();
        }
    }

    void Texture::createGpuObject()
    {
        unsigned int id;
        GL(glGenTextures(1, &id));

        setGpuObjectId(id);
    }

    void Texture::destroyGpuObject()
    {
        unsigned int id = getGpuObjectId();
        glDeleteTextures(1, &id);

        unsetGpuObjectId();
    }
}
