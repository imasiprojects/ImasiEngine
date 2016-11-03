#include "Texture.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    std::map<unsigned int, unsigned int> Texture::_indexTypes;

    void Texture::bind(Texture* texture, unsigned int index)
    {
        unsigned int type = texture->getTextureType();

        _indexTypes[index] = type;

        GL(glActiveTexture(GL_TEXTURE0 + index));
        GL(glEnable(type));
        GL(glBindTexture(type, texture->getGpuId()));
    }

    void Texture::unbind(unsigned int index)
    {
        auto indexIterator = _indexTypes.find(index);

        if (indexIterator != _indexTypes.end())
        {
            unsigned int type = indexIterator->second;

            GL(glActiveTexture(GL_TEXTURE0 + index));
            GL(glBindTexture(type, UNBIND));
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
        if (Texture::isValidGpuId())
        {
            Texture::destroyGpuObject();
        }
    }

    void Texture::createGpuObject()
    {
        unsigned int gpuId;
        GL(glGenTextures(1, &gpuId));

        setGpuId(gpuId);
    }

    void Texture::destroyGpuObject()
    {
        unsigned int gpuId = getGpuId();
        glDeleteTextures(1, &gpuId);

        unsetGpuId();
    }
}
