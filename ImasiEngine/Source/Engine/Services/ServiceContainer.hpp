#ifndef IMASIENGINE_SERVICECONTAINER_HPP
#define IMASIENGINE_SERVICECONTAINER_HPP

#include <map>

#include "Service.hpp"

namespace ImasiEngine
{
    class ServiceContainer
    {
    private:

        using TypeId = void*;
        std::map<TypeId, Service*> _instances;

    public:

        template <typename T>
        static TypeId getTypeId()
        {
            return (TypeId)&getTypeId<T>;
        }

        template <typename T,
            typename = typename std::enable_if<
                std::is_assignable<Service, T>::value
                && !std::is_same<Service, T>::value
            >::type
        >
        void add(T* instance)
        {
            _instances[getTypeId<T>()] = instance;
        }

        template <typename T,
            typename = typename std::enable_if<
                std::is_assignable<Service, T>::value
                && !std::is_same<Service, T>::value
            >::type
        >
        T* get()
        {
            return (T*)_instances[getTypeId<T>()];
        }

        const std::map<TypeId, Service*>& getAll() const
        {
            return _instances;
        }
    };
}

#endif
