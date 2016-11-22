#ifndef IMASIGAME_SERVICECONTAINER_HPP
#define IMASIGAME_SERVICECONTAINER_HPP

namespace Imasi
{
    typedef size_t TypeId;

    class ServiceContainer
    {
    private:

        std::map<TypeId, void*> _instances;

    public:

        template <typename T>
        static TypeId getTypeId()
        {
            return typeid(T).hash_code();
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
