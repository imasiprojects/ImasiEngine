#ifndef IMASIENGINE_APPLY_HPP
#define IMASIENGINE_APPLY_HPP

#include <tuple>
#include <tuple>

namespace ImasiEngine
{
    template<typename TFunc, typename... TTuple, size_t... Indices>
    constexpr decltype(auto) applySequence(
        const TFunc& functor,
        const std::tuple<TTuple...>& tuple,
        const std::index_sequence<Indices...>&)
    {
        return functor(std::get<Indices>(tuple)...);
    }

    template<typename TFunc, typename... TTuple>
    constexpr decltype(auto) applyTuple(
        const TFunc& functor,
        const std::tuple<TTuple...>& tuple)
    {
        return applySequence(functor, tuple, std::index_sequence_for<TTuple...>());
    }
}

#endif
