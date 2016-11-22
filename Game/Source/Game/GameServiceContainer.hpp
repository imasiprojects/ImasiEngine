#ifndef IMASIGAME_GAMESERVICECONTAINER_HPP
#define IMASIGAME_GAMESERVICECONTAINER_HPP

#include "../Services/DemoService.hpp"

namespace Imasi
{
    class GameServiceContainer
    {
    public:

        DemoService* myDemoService;
    };
}

#endif
