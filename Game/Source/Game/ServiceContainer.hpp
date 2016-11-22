#ifndef IMASIGAME_SERVICECONTAINER_HPP
#define IMASIGAME_SERVICECONTAINER_HPP

#include <map>

namespace Imasi
{
    typedef unsigned int TypeId;

    class ServiceContainer
    {
    private:

        static unsigned int idCount;
        std::map<TypeId, void*> _instances;

    public:

        template <typename T>
        static TypeId getTypeId()
        {
            static unsigned int id = idCount++;
            return id;
        }

        // TODO: Destructor (clean instances)

        template <typename T>
        void regisster(T* instance)
        {
            _instances[getTypeId<T>()] = instance;
        }

        template <typename T>
        T* get()
        {
            return (T*)_instances[getTypeId<T>()];
        }
    };
}

#endif
