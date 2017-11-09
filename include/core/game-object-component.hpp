#pragma once

namespace MNPCore {
    class Engine;

    template <class GameObjContext>
    class GameObjectComponent {
    public:
        GameObjectComponent(){}
        virtual void onLoad(Engine &engineContext, GameObjContext &objContext) = 0;
        virtual void onEnter(Engine &engineContext, GameObjContext &objContext) = 0;
        virtual void onUpdate(Engine &engineContext, GameObjContext &objContext, const float &deltaTime) = 0;
        virtual void onExit(Engine &engineContext, GameObjContext &objContext) = 0;
        virtual void onUnload(Engine &engineContext, GameObjContext &objContext) = 0;
    };
}
