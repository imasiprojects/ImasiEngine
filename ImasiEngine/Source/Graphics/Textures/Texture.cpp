#include "Texture.hpp"

#include <GL/glew.h>

#include "../../Utils/Opengl.hpp"

namespace ImasiEngine
{
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
        : _id(UNSET)
        , _type(UNSET)
    {
    }

    Texture::~Texture()
    {
        if (_id != UNSET)
        {
            glDeleteTextures(1, &_id);
        }
    }
}
