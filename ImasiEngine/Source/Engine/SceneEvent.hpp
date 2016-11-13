#ifndef IMASIENGINE_SCENEEVENT_HPP
#define IMASIENGINE_SCENEEVENT_HPP

namespace ImasiEngine
{
    class Scene;

    enum SceneEventType
    {
        NewScene,
        End
    };

    struct SceneEvent
    {
        SceneEventType type;

        union
        {
            Scene* newScene;
        };
    };
}

#endif