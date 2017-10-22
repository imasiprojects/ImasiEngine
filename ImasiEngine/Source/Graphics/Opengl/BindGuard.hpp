#ifndef IMASIENGINE_BINDGUARD_HPP
#define IMASIENGINE_BINDGUARD_HPP

namespace ImasiEngine
{
    template<typename T, typename... TArgs>
    class BindGuard
    {
    private:

#ifdef DEBUG
        bool _isMoved;
        std::tuple<TArgs...> _args;

        template<std::size_t... Indices>
        inline constexpr void unbind(std::index_sequence<Indices...>) const
        {
            T::unbind(std::get<Indices>(_args)...);
        }
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
        inline BindGuard(BindGuard&& other) = default;
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
                unbind(std::index_sequence_for<TArgs...>());
            }
        }
#endif
    };
}

#endif
