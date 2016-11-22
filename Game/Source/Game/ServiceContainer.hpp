#ifndef IMASIGAME_SERVICECONTAINER_HPP
#define IMASIGAME_SERVICECONTAINER_HPP

#include <map>

namespace Imasi
{
    class ServiceContainer
    {
    private:

        using TypeId = void*;
        std::map<TypeId, void*> _instances;

    public:

        template <typename T>
        static TypeId getTypeId()
        {
            return (TypeId)&getTypeId<T>;
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
