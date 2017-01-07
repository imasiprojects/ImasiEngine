#ifndef IMASIGAME_GAMEENGINE_HPP
#define IMASIGAME_GAMEENGINE_HPP

#include "../../ImasiEngine/Source/ImasiEngine.hpp"
#include "GameContext.hpp"

namespace Imasi
{
    class GameEngine : public ImasiEngine::Engine
    {
    private:

        GameContext* _context;

    public:

        GameEngine();
        ~GameEngine();

        void run();
    };
}

#endif
