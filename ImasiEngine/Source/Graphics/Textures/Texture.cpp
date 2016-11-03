#include "Texture.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
    std::map<unsigned int, unsigned int> Texture::_indexTypes;

    void Texture::bind(Texture* texture, unsigned int index)
    {
        _indexTypes[index] = texture->_type;

        GL(glActiveTexture(GL_TEXTURE0 + index));
        GL(glEnable(texture->_type));
        GL(glBindTexture(texture->_type, texture->_id));
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
        , _type(UNSET)
    {
    }

    Texture::Texture(Texture&& texture) noexcept
        : GpuObject(std::move(texture))
        , _type(texture._type)
    {
    }

    Texture::~Texture()
    {
        if (Texture::isValid())
        {
            glDeleteTextures(1, &_id);
        }
    }
}
