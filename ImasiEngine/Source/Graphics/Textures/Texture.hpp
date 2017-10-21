#ifndef IMASIENGINE_TEXTURE_HPP
#define IMASIENGINE_TEXTURE_HPP

#include <map>

#include "../Opengl/GLObject.hpp"
#include "../Opengl/Enums/TextureType.hpp"

namespace ImasiEngine
{
    class Texture
        : public GLObject
    {
    protected:

        static std::map<unsigned int, GLEnums::TextureType> _indexTypes;

        Texture();
        Texture(const Texture&) = delete;
        Texture(Texture&& texture) noexcept;
        virtual ~Texture();

        void createGLObject() override;
        void destroyGLObject() override;

    public:

        static void bind(const Texture& texture, unsigned int index = 0);
        static void unbind(unsigned int index = 0);

        virtual GLEnums::TextureType getGLTextureType() const = 0;
    };
}

#endif
