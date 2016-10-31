#pragma once

#include "../../ImasiEngine/Source/Engine.hpp"
#include "Game/GameContext.hpp"

namespace Imasi
{
    class Game : public ImasiEngine::Engine
    {
    public:

        Game()
        {
            GameContext* gameContext = new GameContext();
            gameContext->level = 666;

            _context = gameContext;
        }
    };
}
