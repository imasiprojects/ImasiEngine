#pragma once
#include <map>

namespace ImasiEngine
{
    class Texture
    {
    protected:

        static std::map<unsigned int, unsigned int> _indexTypes;

        unsigned int _id;
        unsigned int _type;

    public:

        static void bind(Texture* texture, unsigned int index = 0);
        static void unbind(unsigned int index = 0);

        Texture();
        virtual ~Texture();
    };
}
