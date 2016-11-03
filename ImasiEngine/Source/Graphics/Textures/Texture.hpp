#pragma once

#include <map>

#include "../GpuObject.hpp"

namespace ImasiEngine
{
    class Texture : public GpuObject
    {
    protected:

        static std::map<unsigned int, unsigned int> _indexTypes;

        Texture();
        Texture(const Texture&) = delete;
        Texture(Texture&& texture) noexcept;
        virtual ~Texture();

        void createGpuObject() override;
        void destroyGpuObject() override;

        virtual unsigned int getOpenglTextureType() const = 0;

    public:

        static void bind(Texture* texture, unsigned int index = 0);
        static void unbind(unsigned int index = 0);
    };
}
