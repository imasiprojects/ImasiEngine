#ifndef IMASIENGINE_GLBINDGUARD_HPP
#define IMASIENGINE_GLBINDGUARD_HPP

namespace ImasiEngine
{
    template <
        typename T,
        typename... TArgs>
    class BindGuard
    {
        bool _isMoved;
        #ifdef DEBUG
        std::tuple<TArgs...> _args;
        #endif

    public:

        inline BindGuard(const T& object, TArgs&&... args)
            : _isMoved(false)
            #ifdef DEBUG
            , _args(std::make_tuple(std::forward<TArgs>(args)...))
            #endif
        {
            T::bind(object, std::forward<TArgs>(args)...);
        }

        BindGuard(const BindGuard&) = delete;

        BindGuard(BindGuard&& other)
            : _isMoved(false)
            #ifdef DEBUG
            , _args(std::move(other._args))
            #endif
        {
            other._isMoved = true;
        }

        #ifdef DEBUG
        inline virtual ~BindGuard()
        {
            if (!_isMoved)
            {
                unbind(std::index_sequence_for<TArgs...>());
            }
        }

        template<std::size_t... Is>
        constexpr void unbind(std::index_sequence<Is...>) const
        {
            T::unbind(std::get<Is>(_args)...);
        }
        #endif
    };
}

#endif
