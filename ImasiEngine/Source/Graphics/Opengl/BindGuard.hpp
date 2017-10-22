#ifndef IMASIENGINE_BINDGUARD_HPP
#define IMASIENGINE_BINDGUARD_HPP

#include "../../Utils/Apply.hpp"

namespace ImasiEngine
{
    template<typename T, typename... TArgs>
    class BindGuard
    {
    private:

#ifdef DEBUG
        bool _isMoved;
        std::tuple<TArgs...> _args;
#endif

    public:

        inline BindGuard(const T& object, TArgs&&... args)
#ifdef DEBUG
            : _isMoved(false)
            , _args(std::make_tuple(std::forward<TArgs>(args)...))
#endif
        {
            T::bind(object, std::forward<TArgs>(args)...);
        }

        BindGuard(const BindGuard&) = delete;

#ifndef DEBUG
        inline BindGuard(BindGuard&& other) noexcept = default;
#else
        inline BindGuard(BindGuard&& other)
            : _isMoved(false)
            , _args(std::move(other._args))
        {
            other._isMoved = true;
        }

        inline virtual ~BindGuard()
        {
            if (!_isMoved)
            {
                ImasiEngine::apply_tuple(T::unbind, _args);
            }
        }
#endif
    };
}

#endif
