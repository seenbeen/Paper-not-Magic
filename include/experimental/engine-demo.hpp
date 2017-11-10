#include <engine/core/engine.hpp>
#include <engine/core/stage.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>

namespace Experimental { namespace EngineDemos {
    using namespace MNPCore;
    using namespace MNPRender;

    class ObjectA;
    class ComponentA : public GameObjectComponent<ObjectA> {
    public:
        void onLoad(Engine &engineContext, ObjectA &objContext);
        void onEnter(Engine &engineContext, ObjectA &objContext);
        void onUpdate(Engine &engineContext, ObjectA &objContext, const float &deltaTime);
        void onExit(Engine &engineContext, ObjectA &objContext);
        void onUnload(Engine &engineContext, ObjectA &objContext);
    };

    class ObjectA : public GameObject<ObjectA> {
    public:
        float timeOfExistence;
        ObjectA();
    };

    enum EngineStages { MENU, GAME };

    class StageA : public Stage<EngineStages> {
    public:
        StageA();
        void onEnter(Engine &engineContext);
        void onUpdate(Engine &engineContext, const float &deltaTime);
        void onExit(Engine &EngineContext);
    };

    class EngineDemoA {
    public:
        int run();
    };
}}
