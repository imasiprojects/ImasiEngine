#ifndef IMASIGAME_GAMEENGINE_HPP
#define IMASIGAME_GAMEENGINE_HPP

#include "../../ImasiEngine/Source/ImasiEngine.hpp"

namespace Imasi
{
    class DemoEngine : public ImasiEngine::Engine
    {
    private:

    public:

        DemoEngine();
        ~DemoEngine();

        void run();
    };
}

#endif
