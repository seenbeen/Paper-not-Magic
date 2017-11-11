#pragma once

namespace MNPCore {
    class Engine;
    class GameObject;

    class GameObjectComponent {
    public:
        GameObjectComponent(){}
        virtual ~GameObjectComponent(){}

        virtual void onLoad(Engine &engineContext, GameObject &objContext) = 0;
        virtual void onEnter(Engine &engineContext, GameObject &objContext) = 0;
        virtual void onUpdate(Engine &engineContext, GameObject &objContext, const float &deltaTime) = 0;
        virtual void onPostUpdate(Engine &engineContext, GameObject &objContext) = 0;
        virtual void onExit(Engine &engineContext, GameObject &objContext) = 0;
        virtual void onUnload(Engine &engineContext, GameObject &objContext) = 0;
    };
}
