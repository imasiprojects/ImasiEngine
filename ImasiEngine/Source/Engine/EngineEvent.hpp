#ifndef IMASIENGINE_ENGINEEVENT_HPP
#define IMASIENGINE_ENGINEEVENT_HPP

namespace ImasiEngine
{
    class Scene;

    enum EngineEventType
    {
        Start,
        ChildEnded
    };

    struct EngineEvent
    {
        EngineEventType type;

        union
        {
            Scene* endedChild;
        };
    };
}

#endif
