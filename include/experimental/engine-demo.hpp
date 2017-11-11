#include <engine/core/engine.hpp>
#include <engine/core/stage.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>

namespace Experimental { namespace EngineDemos {
    using namespace MNPCore;
    using namespace MNPRender;

    class ComponentA : public GameObjectComponent {
        float m_timeOfExistence;
    public:
        void onLoad(Engine &engineContext, GameObject &objContext);
        void onEnter(Engine &engineContext, GameObject &objContext);
        void onUpdate(Engine &engineContext, GameObject &objContext, const float &deltaTime);
        void onPostUpdate(Engine &engineContext, GameObject &objContext);
        void onExit(Engine &engineContext, GameObject &objContext);
        void onUnload(Engine &engineContext, GameObject &objContext);
    };

    class ObjectA : public GameObject {
    public:
        ObjectA();
    };

    enum EngineStages { MENU, GAME };

    class StageA : public Stage<EngineStages> {
    public:
        StageA();
        void onEnter(Engine &engineContext);
        void onUpdate(Engine &engineContext, const float &deltaTime);
        void onPostUpdate(Engine &engineContext);
        void onExit(Engine &EngineContext);
    };

    class EngineDemoA {
    public:
        int run();
    };
}}
