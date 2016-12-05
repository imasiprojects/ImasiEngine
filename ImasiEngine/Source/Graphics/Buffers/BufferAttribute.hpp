#ifndef IMASIENGINE_BUFFERATTRIBUTE_HPP
#define IMASIENGINE_BUFFERATTRIBUTE_HPP

namespace ImasiEngine
{
    struct BufferAttribute
    {
        unsigned int componentCount;
        unsigned int membersPerComponent;
        unsigned int sizeOfComponent = 0;
        void* componentOffset = nullptr;
    };
}

#endif
