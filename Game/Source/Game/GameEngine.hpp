#ifndef IMASIGAME_GAMEENGINE_HPP
#define IMASIGAME_GAMEENGINE_HPP

#include "../../ImasiEngine/Source/Engine.hpp"
#include "GameContext.hpp"
#include "GameServiceContainer.hpp"

namespace Imasi
{
    class GameEngine : public ImasiEngine::Engine
    {
    private:

        GameContext* _context;
        GameServiceContainer* _serviceContainer;

    public:

        GameEngine();
        ~GameEngine();

        void run();
    };
}

#endif
