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
        Cached<T>& operator=(AssignArg arg)
        {
            _value = arg;
            return *this;
        }

        operator T&()
        {
            return _value;
        }

        T& value() const
        {
            return _value;
        }

        void set(const T& value)
        {
            _value = value;
        }

        void validate()
        {
            _isValid = true;
        }

        void invalidate()
        {
            _isValid = false;
        }

        bool isValid() const
        {
            return _isValid;
        }

        bool isInvalid() const
        {
            return !_isValid;
        }
    };
}

#endif
