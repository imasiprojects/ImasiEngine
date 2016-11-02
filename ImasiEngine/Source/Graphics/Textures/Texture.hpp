#pragma once

#include <map>

#include "../GpuObject.hpp"

namespace ImasiEngine
{
    class Texture : public GpuObject
    {
    protected:

        static std::map<unsigned int, unsigned int> _indexTypes;

        unsigned int _type;

        Texture();
        Texture(const Texture&) = delete;
        Texture(Texture&& texture) noexcept;
        virtual ~Texture();

    public:

        static void bind(Texture* texture, unsigned int index = 0);
        static void unbind(unsigned int index = 0);
    };
}
