#ifndef IMASIENGINE_SERVICE_HPP
#define IMASIENGINE_SERVICE_HPP

namespace ImasiEngine
{
    class Service
    {
    protected:

        Service()
        {
        }

        virtual ~Service()
        {
        }

    public:

        // TODO: processEngineEvent?
        virtual void update();
    };
}

#endif
