#include <iostream>

#include <core/engine.hpp>
#include <core/stage.hpp>
#include <core/gameobject.hpp>
#include <core/gameobjectcomponent.hpp>

using namespace MNPCore;

class ObjectA;
class ComponentA : public GameObjectComponent<ObjectA> {
public:
    void onLoad(Engine &engineContext, ObjectA &objContext);
    void onEnter(Engine &engineContext, ObjectA &objContext);
    void onUpdate(Engine &engineContext, ObjectA &objContext);
    void onExit(Engine &engineContext, ObjectA &objContext);
    void onUnload(Engine &engineContext, ObjectA &objContext);
};

class ObjectA : public GameObject<ObjectA> {
public:
    int framesOfExistance;
    ObjectA() : GameObject(*this) {
        framesOfExistance = 0;
        addComponent(new ComponentA());
    }
};

void ComponentA::onLoad(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Load" << std::endl;
}
void ComponentA::onEnter(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Enter" << std::endl;
}
void ComponentA::onUpdate(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Update Frame: " << objContext.framesOfExistance++ << std::endl;
    if (objContext.framesOfExistance == 5) {
        engineContext.stop();
    }
}
void ComponentA::onExit(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Exit" << std::endl;
}
void ComponentA::onUnload(Engine &engineContext, ObjectA &objContext) {
    std::cout << "ComponentA on Unload" << std::endl;
}

enum EngineStages { MENU, GAME };

class StageA : public Stage<EngineStages> {
public:
    StageA() : Stage(GAME) {
        addObject(new ObjectA());
    }
    void onEnter(Engine &engineContext) {
        std::cout << "StageA onEnter" << std::endl;
    };
    void onUpdate(Engine &engineContext) {
        std::cout << "StageA onUpdate" << std::endl;
    };
    void onExit(Engine &EngineContext) {
        std::cout << "StageA onExit" << std::endl;
    };
};

int main() {
    Engine engine;

    std::vector<Stage<EngineStages>*> stages;
    stages.push_back(new StageA());

    BaseEngineConfig *config = new EngineConfig<EngineStages>(GAME, stages);
    engine.initialize(config);

    delete config;

    engine.run();

    engine.shutdown();

    return 0;
}
