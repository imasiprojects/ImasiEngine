#ifndef IMASIGAME_GAMESERVICE_HPP
#define IMASIGAME_GAMESERVICE_HPP

namespace Imasi
{
    class DemoService
        : public ImasiEngine::Service
    {
    private:

        int _number;

    public:

        DemoService()
            : Service()
            , _number(0)
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

        void update() override
        {
            increment();
        }
    };
}

#endif