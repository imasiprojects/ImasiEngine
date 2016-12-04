#ifndef IMASIENGINE_CACHED_HPP
#define IMASIENGINE_CACHED_HPP

template<typename T>
class Cached
{
    T _value;
    bool _isValid;

public:

    template<typename ...ConstructorArgs>
    explicit Cached(ConstructorArgs ...args)
        : _value(args...)
        , _isValid(true)
    {
    }

    template<
        typename = std::enable_if<
            std::is_copy_constructible<T>::value
        >
    >
    explicit Cached(const Cached<T>& cached)
        : _value(cached._value)
        , _isValid(cached._isValid)
    {
    }

    template<
        typename = std::enable_if<
            std::is_move_constructible<T>::value
        >
    >
    explicit Cached(Cached<T>&& cached)
        : _value(std::forward(cached._value))
        , _isValid(cached._isValid)
    {
    }

    template<
        typename AssignArg,
        typename = std::enable_if<
            std::is_assignable<T, AssignArg>::value
        >
    >
    Cached<T>& operator=(AssignArg arg)
    {
        _value = arg;
        _isValid = true;
        return *this;
    }

    operator T&()
    {
        return _value;
    }

    T& get() const
    {
        return _value;
    }

    void set(const T& newValue)
    {
        _value = newValue;
        _isValid = true;
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
};

#endif
