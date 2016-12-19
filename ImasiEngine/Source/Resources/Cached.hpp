#ifndef IMASIENGINE_CACHED_HPP
#define IMASIENGINE_CACHED_HPP

namespace ImasiEngine
{
    template<typename T>
    class Cached
    {
    private:

        T _value;
        bool _isValid;

    public:

        template<
            typename ...ConstructorArgs,
            typename = typename std::enable_if<
                std::is_constructible<T, ConstructorArgs...>::value
            >::type
        >
        explicit Cached(ConstructorArgs ...args)
            : _value(args...)
            , _isValid(true)
        {
        }

        template<
            typename = typename std::enable_if<
                std::is_copy_constructible<T>::value
            >::type
        >
        explicit Cached(const Cached<T>& cached)
            : _value(cached._value)
            , _isValid(cached._isValid)
        {
        }

        template<
            typename = typename std::enable_if<
                std::is_move_constructible<T>::value
            >::type
        >
        explicit Cached(Cached<T>&& cached)
            : _value(std::move(cached._value))
            , _isValid(cached._isValid)
        {
        }

        template<
            typename AssignArg,
            typename = typename std::enable_if<
                std::is_assignable<T, AssignArg>::value
            >::type
        >
        const Cached<T>& operator=(AssignArg arg)
        {
            _value = arg;
            return *this;
        }

        operator const T&()
        {
            return _value;
        }

        const T& value() const
        {
            return _value;
        }

        void setCache(const T& value)
        {
            _value = value;
        }

        void validateCache()
        {
            _isValid = true;
        }

        void invalidateCache()
        {
            _isValid = false;
        }

        bool hasValidCache() const
        {
            return _isValid;
        }

        bool hasInvalidCache() const
        {
            return !_isValid;
        }
    };
}

#endif
