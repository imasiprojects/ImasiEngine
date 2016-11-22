#ifndef IMASIGAME_GAMESERVICE_HPP
#define IMASIGAME_GAMESERVICE_HPP

namespace Imasi
{
    class DemoService
    {
    private:

        int _number;

    public:

        DemoService()
            : _number(0)
        {
        }

        ~DemoService()
        {
        }

        int getNumber() const
        {
            return _number;
        }

        void increment()
        {
            _number++;
        }
    };
}

#endif