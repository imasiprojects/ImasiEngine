#pragma once

#include "../../ImasiEngine/Source/Engine.hpp"
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
    };
}
