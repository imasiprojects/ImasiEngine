#ifndef IMASIENGINE_APPLY_HPP
#define IMASIENGINE_APPLY_HPP

#include <iostream>

namespace ImasiEngine
{
    template<
        typename TFunc,
        typename... TTuple,
        std::size_t... Indices>
        inline constexpr decltype(auto) apply_sequence(
            const TFunc& functor,
            const std::tuple<TTuple...>& tuple,
            const std::index_sequence<Indices...>&)
    {
        return functor(std::get<Indices>(tuple)...);
    }

    template<
        typename TFunc,
        typename... TTuple>
        inline constexpr decltype(auto) apply_tuple(
            const TFunc& functor,
            const std::tuple<TTuple...>& tuple)
    {
        return apply_sequence(functor, tuple, std::index_sequence_for<TTuple...>());
    }
}

#endif
