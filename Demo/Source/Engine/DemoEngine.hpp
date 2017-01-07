#ifndef IMASIGAME_GAMEENGINE_HPP
#define IMASIGAME_GAMEENGINE_HPP

#include "../../ImasiEngine/Source/ImasiEngine.hpp"
#include "DemoContext.hpp"

namespace Imasi
{
    class DemoEngine : public ImasiEngine::Engine
    {
    private:

        DemoContext* _context;

    public:

        DemoEngine();
        ~DemoEngine();

        void run();
    };
}

#endif
