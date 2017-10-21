#ifndef IMASIENGINE_GLBINDGUARD_HPP
#define IMASIENGINE_GLBINDGUARD_HPP

namespace ImasiEngine
{
    template <
        typename T,
        typename... TArgs>
    class BindGuard
    {
    private:

        bool _isMoved;
#ifdef DEBUG
        std::tuple<TArgs...> _args;

        template<std::size_t... Indices>
        inline constexpr void unbind(std::index_sequence<Indices...>) const
        {
            T::unbind(std::get<Indices>(_args)...);
        }
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

        inline BindGuard(BindGuard&& other)
            : _isMoved(false)
#ifdef DEBUG
            , _args(std::move(other._args))
#endif
        {
            other._isMoved = true;
        }

        inline virtual ~BindGuard()
        {
#ifdef DEBUG
            if (!_isMoved)
            {
                unbind(std::index_sequence_for<TArgs...>());
            }
#endif
        }
    };
}

#endif
