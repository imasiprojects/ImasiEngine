#ifndef IMASIGAME_GAMEENGINE_HPP
#define IMASIGAME_GAMEENGINE_HPP

#include "../../ImasiEngine/Source/Engine.hpp"
#include "../Services/DemoService.hpp"
#include "GameContext.hpp"

namespace Imasi
{
    class GameEngine : public ImasiEngine::Engine
    {
    private:

        GameContext* _context;
        DemoService* _demoService;

    public:

        GameEngine();
        ~GameEngine();

        void run();
    };
}

#endif
