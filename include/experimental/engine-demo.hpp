#include <engine/core/engine.hpp>
#include <engine/core/stage.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>

namespace Experimental { namespace EngineDemos {
    class ComponentA : public MNPCore::GameObjectComponent {
        float m_timeOfExistence;
    public:
        void onLoad(MNPCore::Engine &engineContext);
        void onEnter(MNPCore::Engine &engineContext);
        void onUpdate(MNPCore::Engine &engineContext, const float &deltaTime);
        void onPostUpdate(MNPCore::Engine &engineContext);
        void onExit(MNPCore::Engine &engineContext);
        void onUnload(MNPCore::Engine &engineContext);
    };

    class ObjectA : public MNPCore::GameObject {
    public:
        ObjectA();
    };

    enum EngineStages { MENU, GAME };

    class StageA : public MNPCore::Stage<EngineStages> {
    public:
        StageA();
        void onEnter(MNPCore::Engine &engineContext);
        void onUpdate(MNPCore::Engine &engineContext, const float &deltaTime);
        void onPostUpdate(MNPCore::Engine &engineContext);
        void onExit(MNPCore::Engine &EngineContext);
    };

    class EngineDemoA {
    public:
        int run();
    };
}}
