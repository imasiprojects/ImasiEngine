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
        unsigned int type = _indexTypes[index];

        GL(glActiveTexture(GL_TEXTURE0 + index));
        GL(glBindTexture(type, UNBIND));
        GL(glDisable(type));

        _indexTypes.erase(_indexTypes.find(index));
    }

    Texture::Texture() :
        _type(UNSET)
    {
        glGenTextures(1, &_id);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &_id);
    }
}
