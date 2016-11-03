#pragma once

#include <map>

#include "../GLObject.hpp"

namespace ImasiEngine
{
    class Texture : public GLObject
    {
    protected:

        static std::map<unsigned int, unsigned int> _indexTypes;

        Texture();
        Texture(const Texture&) = delete;
        Texture(Texture&& texture) noexcept;
        virtual ~Texture();

        void createGLObject() override;
        void destroyGLObject() override;

        virtual unsigned int getOpenglTextureType() const = 0;

    public:

        static void bind(Texture* texture, unsigned int index = 0);
        static void unbind(unsigned int index = 0);
    };
}
